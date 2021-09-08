#include "board.hpp"

Board::Board(QObject *parent): QGraphicsScene(parent) {
    qDebug() << "Board ctor";
    background_ = background_.scaledToHeight(Constants::squareSize * Constants::boardHeight + 4000);
    QGraphicsPixmapItem *pix = addPixmap(background_);
    pix->setPos((Constants::totalWidth - background_ .width()) / 2,
                (Constants::totalHeight - background_.height()) / 2);

    setupBoard();
}
Board::~Board() {
    //delete ui_;
}

void Board::setupBoard() {

    QPixmap pix(Constants::squareSize, Constants::squareSize);
    pix.fill(QColor(0, 255, 0, 100));
    selectedMask_.setPixmap(pix);
    selectedMask_.hide();
    selectedMask_.setZValue(3);
    addItem(&selectedMask_);

    addItem(&rangeIndicator);
    rangeIndicator.setZValue(10);
    connect(&menu, SIGNAL(abilityClicked()), this, SLOT(onAbilityClick()));
    connect(&menu, SIGNAL(attackClicked()), this, SLOT(onAttackClick()));
    connect(&menu, SIGNAL(selectClicked()), this, SLOT(onSelectClick()));
    connect(&menu, SIGNAL(skipClicked()), this, SLOT(onSkipClick()));

    addItem(&menu);

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


    qDebug() << "Constructing terrain";
    // constructing terrain
    RandomInt randomInt(1, 10);
    for (int i = 0; i < Constants::boardWidth; i++) {
        for (int j = 0; j < Constants::boardHeight; j++) {
            if (randomInt.get() == 1 && !(squares[i][j]->piece())) {
                squares[i][j]->setTerrain(new Rock());
            } else {
                squares[i][j]->setTerrain(new Grass());
            }
            squares[i][j]->terrain()->setCoordinates(QPoint(i, j));
            addItem(squares[i][j]->terrain());
        }
    }

    qDebug() << "Constructing consumbles";

    RandomInt randomConsumable = RandomInt(0, ConsumableTypes.size() - 1);
    for (int i = 0; i < Constants::boardWidth; i++) {
        for (int j = 0; j < Constants::boardHeight; j++) {
            if (randomInt.get() == 1 && squares[i][j]->occupiable()) {
                qDebug() << "setting consumable";
                auto c = buildConsumable(ConsumableTypes[randomConsumable.get()]);
                qDebug() << (int)c;
                squares[i][j]->setConsumable(c);
                qDebug() << "setting point";
                squares[i][j]->consumable()->setCoordinates(QPoint(i, j));
                qDebug() << "adding con";
                addItem(squares[i][j]->consumable());
            }
        }
    }


    qDebug() << "Connecting buttons";


    updateVision();

    qDebug() << "Finished setupBoard";

}

void Board::showSelected() {
    if (!selectedPiece) {
        selectedMask_.hide();
    } else {
        selectedMask_.setPos(selectedPiece->coordinates() * Constants::squareSize);
        selectedMask_.show();
    }

}

void Board::showMoves() {
    static std::vector<Square*> occupiableSquares;
    for (auto occupiableSquare: occupiableSquares) {
        occupiableSquare->showOccupiable(false);
    }
    occupiableSquares.clear();
    if (!selectedPiece) {
        return;
    }
    for (const auto& move: moves) {
        QPoint newCoord = selectedPiece->coordinates() + move;
        if (!onBoard(newCoord)) {
            continue;
        }
        Square* newSquare = squares[newCoord.x()][newCoord.y()];
        if (newSquare->occupiable()) {
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
    newSquare->setPiece(oldSquare->piece());
    newSquare->piece()->setCoordinates(newSquare->coordinates());
    oldSquare->setPiece(nullptr);
    updateVision();

}

void Board::showRange(Piece *piece) {
    //qDebug() << "Showing range";
    if (!piece) {
        //qDebug() << "Deleting range";
        rangeIndicator.hide();
        return;
    }

    //qDebug() << "Showing Range" << piece->coordinates();

    int range = piece->getStat("range");

    QPoint start(0, range + 1);
    QPoint startPoint = start;
    QPoint endPoint;
    QPoint dx(1, 0);
    QPoint dy(0, -1);
    bool dodx = true;
    QVector<QPointF> points;

    do {
        endPoint = startPoint + (dodx ? dx : dy);
        QPoint startPointOffset = piece->coordinates() + startPoint;
        QPoint endPointOffset = piece->coordinates() + endPoint;
        if (onBoard(startPointOffset) && onBoardOffset(endPointOffset) ||
            onBoardOffset(startPointOffset) && onBoard(endPointOffset)) {
            points.push_back(startPointOffset * Constants::squareSize);
            points.push_back(endPointOffset * Constants::squareSize);
        }

        startPoint = endPoint;

        if (startPoint == QPoint(range + 1, 0)) {

            dx = QPoint(-1, 0);
            dodx = true;
            continue;
        } else if (startPoint == QPoint(0, -range)) {
            dy = QPoint(0, 1);
            dodx = false;
            continue;
        } else if (startPoint == (QPoint(-range, 0))) {
            dx = QPoint(1, 0);
            dodx = false;
            continue;
        }

        dodx = !dodx;


    } while (startPoint != start);

    rangeIndicator.setPolygon(QPolygonF(points));
    rangeIndicator.setPen(QPen(QBrush(QColor(0, 200, 255)), 10));
    rangeIndicator.show();

    update();

}

void Board::updateVision() {
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
                int vision = piece->getStat("range");
                for (int x = -vision; x <= vision; x++) {
                    for (int y = -(vision - abs(x)); y <= vision - abs(x); y++) {
                        QPoint visionCoord = piece->coordinates() + QPoint(x, y);
                        if (onBoard(visionCoord) && hasVision(piece->coordinates(), visionCoord)) {
                            squares[i + x][j + y]->setPlayerVision(VisionType::visible);
                        }
                    }
                }
            }
        }
    }
    update();
}



bool Board::hasVision(QPoint a, QPoint b) {

    if (a == b) {
        return true;
    }

    QPoint halfSquare(Constants::squareSize / 2, Constants::squareSize / 2);

    QGraphicsLineItem line(QLineF(a * Constants::squareSize + halfSquare, b * Constants::squareSize + halfSquare));
    addItem(&line);

    auto items = collidingItems(&line);
    for (auto item: items) {
        Square* square = dynamic_cast<Square*>(item);
        if (square && square->blocksVision()) {
            if (!(square->coordinates() == a || square->coordinates() == b)) {
                removeItem(&line);
                return false;
            } else {
                return true;
            }

        }
    }
    removeItem(&line);

    return true;

}

