#include "board.hpp"

Board::Board(QObject *parent): QGraphicsScene(parent) {
    qDebug() << "Board ctor";
    background_ = background_.scaledToHeight(Constants::squareSize * Constants::boardHeight + 2000);
    QGraphicsPixmapItem *pix = addPixmap(background_);
    pix->setPos((Constants::totalWidth - background_ .width()) / 2,
                (Constants::totalHeight - background_.height()) / 2);

    setupBoard();
}
Board::~Board() {
    //delete ui_;
}

void Board::setupBoard() {

    abilityButton = new ImageButton(":/res/img/ability.png");
    attackButton  = new ImageButton(":/res/img/attack.png");
    selectButton  = new ImageButton(":/res/img/select.png");
    skipButton    = new ImageButton(":/res/img/skip.png");

    abilityButton->hide();
    attackButton->hide();
    selectButton->hide();
    skipButton->hide();

    connect(abilityButton, SIGNAL(clicked()), this, SLOT(onAbilityClick()));
    connect(attackButton,  SIGNAL(clicked()), this, SLOT(onAttackClick()));
    connect(selectButton,  SIGNAL(clicked()), this, SLOT(onSelectClick()));
    connect(skipButton,    SIGNAL(clicked()), this, SLOT(onSkipClick()));

    addItem(abilityButton);
    addItem(attackButton);
    addItem(selectButton);
    addItem(skipButton);

    infoText = new QGraphicsTextItem("test");
    addItem(infoText);
    infoText->setZValue(10);


    qDebug() << "Constructing squares";
    // constructing squares
    for (int i = 0; i < Constants::boardWidth; i++) {
        squares.push_back(std::vector<Square*>());
        for (int j = 0; j < Constants::boardHeight; j++) {
            squares[i].push_back(new Square(QPoint(i, j)));
            connect(squares[i][j], SIGNAL(squareClicked(Square*)), this, SLOT(onSquareClick(Square*)));
            addItem(squares[i][j]);
        }
    }
    qDebug() << "Constructing terrain";
    // constructing terrain
    RandomInt randomInt(1, 10);
    for (int i = 0; i < Constants::boardWidth; i++) {
        for (int j = 0; j < Constants::boardHeight; j++) {
            if (randomInt.get() == 1 &&
                !(i > Constants::boardWidth / 2 - 5 && i <= Constants::boardWidth / 2 + 3 && // TODO adjust based on playerPiecePosition
                  (j == Constants::boardHeight - 2 || j == Constants::boardHeight - 1))) {
                squares[i][j]->setTerrain(new Rock());
            } else {
                squares[i][j]->setTerrain(new Grass());
            }
            squares[i][j]->terrain()->setCoordinates(QPoint(i, j));
            addItem(squares[i][j]->terrain());
        }
    }
    //constructing pieces

    qDebug() << "Constructing player pieces";

    int xOffset = (Constants::boardWidth - playerPiecePositions[0].size()) / 2;
    int yOffset = Constants::boardHeight - playerPiecePositions.size();
    for (int x = 0; x < playerPiecePositions[0].size(); x++) {
        for (int y = 0; y < playerPiecePositions.size(); y++) {
            //qDebug() << x << y;
            Piece *piece = buildPiece(playerPiecePositions[y][x]);
            piece->setCoordinates(QPoint(x + xOffset, y + yOffset));
            squares[x + xOffset][y + yOffset]->setPiece(piece);
            addItem(piece);

            connect(piece, SIGNAL(hoverEnter(Piece*)), this, SLOT(onPieceHoverEnter(Piece*)));
            connect(piece, SIGNAL(hoverLeave(Piece*)), this, SLOT(onPieceHoverLeave(Piece*)));
            //connect(piece, SIGNAL(selectClicked(Piece*)), this, SLOT(onPieceSelect(Piece*)));
        }
    }

    qDebug() << "Constructing enemy pieces";

    xOffset = (Constants::boardWidth - enemyPiecePositions[0].size()) / 2;
    for (int x = 0; x < enemyPiecePositions[0].size(); x++) {
        for (int y = enemyPiecePositions.size() - 1; y >= 0 ; y--) {
            Piece *piece = buildPiece(enemyPiecePositions[y][x]);
            squares[x + xOffset][y]->setPiece(piece);
            piece->setCoordinates(QPoint(x + xOffset, y));
            addItem(piece);
            connect(piece, SIGNAL(hoverEnter(Piece*)), this, SLOT(onPieceHoverEnter(Piece*)));
            connect(piece, SIGNAL(hoverLeave(Piece*)), this, SLOT(onPieceHoverLeave(Piece*)));
        }
    }

    qDebug() << "Connecting buttons";


    //updateVision();

    qDebug() << "Finished setupBoard";

}



void Board::showMoves(Piece *piece) {
    static std::vector<Square*> occupiableSquares;
    for (auto occupiableSquare: occupiableSquares) {
        occupiableSquare->showOccupiable(false);
    }
    occupiableSquares.clear();
    if (!piece) {
        return;
    }
    for (const auto& move: moves) {
        QPoint newCoord = piece->coordinates() + move;

        if (!onBoard(newCoord)) {
            continue;
        }
        Square* newSquare = squares[newCoord.x()][newCoord.y()];
        if (newSquare->occupiable()) {
            qDebug() << "occupiable newCoord" << newCoord;
            occupiableSquares.push_back(newSquare);
            newSquare->showOccupiable(true);
        }
    }
}
void Board::movePiece(Square* oldSquare, Square* newSquare) {
    qDebug() << "Moving piece from" << oldSquare->coordinates() << "to" << newSquare->coordinates();
    if (!newSquare->occupiable() || dist(oldSquare, newSquare) != 1) {
        return;
    }
    qDebug() << "setting new square";
    newSquare->setPiece(oldSquare->piece());
    newSquare->piece()->setCoordinates(newSquare->coordinates());
    qDebug() << "setting old square";
    oldSquare->setPiece(nullptr);
    updateVision();
    qDebug() << "Finished moving";
    showMoves(newSquare->piece());
    skipButton->setCoordinates(newSquare->coordinates());
    //selectPiece(newSquare->piece());
}



void Board::updateVision() {
    qDebug() << "updating vision";
    for (auto& vec: squares) {
        for (auto& square: vec) {
            if (square->playerVision() == VisionType::visible) {
                square->setPlayerVision(VisionType::seen);
            }
        }
    }
    for (int i = 0; i < Constants::boardWidth; i++) {
        for (int j = 0; j < Constants::boardHeight; j++) {
            Piece *piece = squares[i][j]->piece();
            if (piece && piece->playerPiece()) {
                auto visibleSquares = getVisibleSquares(squares[i][j]);
                for (auto square: visibleSquares) {
                    square->setPlayerVision(VisionType::visible);
                }
            }
        }
    }
    update();
}

std::vector<Square*> Board::getVisibleSquares(Square *square) {
    //qDebug() << "getVisibleSquares";
    std::vector<Square*> visibleSquares;
    Piece *piece = square->piece();
    if (piece) {
        int vision = piece->getStat("range");
        for (int x = -vision; x <= vision; x++) {
            for (int y = -(vision - abs(x)); y <= vision - abs(x); y++) {
                QPoint visionPos = square->coordinates() + QPoint(x, y);
                if (onBoard(visionPos)/* && hasVision(square, squares[visionPos.x()][visionPos.y()])*/) {
                    visibleSquares.push_back(squares[visionPos.x()][visionPos.y()]);
                }
            }
        }
    }
    return visibleSquares;
}

bool Board::hasVision(Piece *a, Piece *b) {

    double x1 = a->pos().x();
    double x2 = b->pos().x();

    double y1 = a->pos().y();
    double y2 = b->pos().y();
    double m = (y2 - y1) / (x2 - x1);
    double c = y1 - x1 * m;

    double minX = x1 < x2 ? x1 : x2;
    double maxX = x1 < x2 ? x2 : x1;

    double minY = y1 < y2 ? y1 : y2;
    double maxY = y1 < y2 ? y2 : y1;


    if (x1 == x2) {
        for (int y = minY; y < maxY; y++) {
            if (squares[x1][y]->blocksVision()) {
                squares[x1][y]->setPlayerVision(VisionType::visible);
                return false;
            }
        }
        return true;
    } else if (y1 == y2) {
        for (int x = minX; x < maxX; x++) {
            if (squares[x][y1]->blocksVision()) {
                squares[x][y1]->setPlayerVision(VisionType::visible);
                return false;
            }
        }
        return true;
    }


    for (int x = minX; x < maxX; x++) {
        int y = m * x + c;
        if (squares[x][y]->blocksVision()) {
            squares[x][y]->setPlayerVision(VisionType::visible);
            return false;
        } else if (squares[x][y + 1 * (m > 0 ? 1 : -1)]->blocksVision()) {
            squares[x][y + 1 * (m > 0 ? 1 : -1)]->setPlayerVision(VisionType::visible);
            return false;
        }
    }


    for (int y = minY; y < maxY; y++) {
        int x = (y - c) / m;
        if (squares[x][y]->blocksVision()) {
            squares[x][y]->setPlayerVision(VisionType::visible);
            return false;
        } else if (squares[x + 1 * (m > 0 ? 1 : -1)][y]->blocksVision()) {
            squares[x + 1 * (m > 0 ? 1 : -1)][y]->setPlayerVision(VisionType::visible);
            return false;
        }
    }




    return true;

}

