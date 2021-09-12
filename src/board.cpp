#include "board.hpp"

#include <windows.h>

Board::Board(QObject *parent): QGraphicsScene(parent) {
    qDebug() << "Board ctor";
    initialSetup();
    setupBoard(1);
}
Board::~Board() {
    //delete ui_;
}

void Board::initialSetup() {
    QPixmap pix;

    pix.load(":/res/img/bg.jpg");
    pix = pix.scaledToHeight(Constants::squareSize * Constants::boardHeight + 4000);
    background_.setPixmap(pix);
    background_.setPos((Constants::totalWidth - pix.width()) / 2, (Constants::totalHeight - pix.height()) / 2);
    background_.setZValue(0);
    addItem(&background_);

    pix.fill(QColor(0, 255, 0, 100));
    pix = pix.scaled(Constants::squareSize, Constants::squareSize);
    selectedMask_.setPixmap(pix);
    selectedMask_.hide();
    selectedMask_.setZValue(3);
    addItem(&selectedMask_);



    rangeIndicator_.setPen(QPen(QBrush(QColor(0, 200, 255)), 10));
    rangeIndicator_.setZValue(4);
    addItem(&rangeIndicator_);


    connect(&menu, SIGNAL(attackClicked()), this, SLOT(onAttackClick()));
    connect(&menu, SIGNAL(selectClicked()), this, SLOT(onSelectClick()));
    connect(&menu, SIGNAL(skipClicked()), this, SLOT(onSkipClick()));
    connect(&menu, SIGNAL(spellClicked()), this, SLOT(onSpellClick()));

    addItem(&menu);
}

void Board::setupBoard(int level) {

    qDebug() << "Setup level" << level << "-------------------------------";


    selectedPiece_ = nullptr;
    focusedPiece_ = nullptr;
    //hoveredPiece_ = nullptr;
    playerTurn_ = true;
    menu.reset();
    rangeIndicator_.hide();
    for (auto& vec: squares_) {
        for (auto square: vec) {
            if (square->consumable()) {
                square->consumable()->hide();
            }
            if (square->terrain()) {
                square->terrain()->hide();
            }
            if (square->piece()) {
                square->piece()->hide();
            }
            square->hide();
        }
    }


    // constructing squares
    int count = 0;
    squares_.clear();
    for (int i = 0; i < Constants::boardWidth; i++) {
        squares_.push_back(std::vector<Square*>());
        for (int j = 0; j < Constants::boardHeight; j++) {
            count++;
            squares_[i].push_back(new Square(QPoint(i, j)));
            connect(squares_[i][j], SIGNAL(squareClicked(Square*)), this, SLOT(onSquareClick(Square*)));
            addItem(squares_[i][j]);
        }
    }

    qDebug() << "Constructing player pieces";

    int xOffset = (Constants::boardWidth - playerPiecePositions[0].size()) / 2;
    int yOffset = Constants::boardHeight - playerPiecePositions.size();
    for (int x = 0; x < playerPiecePositions[0].size(); x++) {
        for (int y = 0; y < playerPiecePositions.size(); y++) {
            Piece *piece = buildPiece(playerPiecePositions[y][x]);
            if (playerPiecePositions[y][x] == PieceType::king) {
                king_ = piece;
            }
            //connect(piece, SIGNAL(hoverEnter(Piece*)), this, SLOT(onPieceHoverEnter(Piece*)));
            //connect(piece, SIGNAL(hoverLeave(Piece*)), this, SLOT(onPieceHoverLeave(Piece*)));
            piece->setCoordinates(QPoint(x + xOffset, y + yOffset));
            squares_[x + xOffset][y + yOffset]->setPiece(piece);
            addItem(piece);
        }
    }

    qDebug() << "Constructing enemy pieces";

    xOffset = (Constants::boardWidth - enemyPiecePositions[0].size()) / 2;
    for (int x = 0; x < enemyPiecePositions[0].size(); x++) {
        for (int y = level - 1/*enemyPiecePositions.size() - 1*/; y >= 0 ; y--) {
            Piece *piece = buildPiece(enemyPiecePositions[0][x]);
            //connect(piece, SIGNAL(hoverEnter(Piece*)), this, SLOT(onPieceHoverEnter(Piece*)));
            //connect(piece, SIGNAL(hoverLeave(Piece*)), this, SLOT(onPieceHoverLeave(Piece*)));
            squares_[x + xOffset][y]->setPiece(piece);
            piece->setCoordinates(QPoint(x + xOffset, y));
            addItem(piece);

        }
    }


    qDebug() << "Constructing terrain";
    // constructing terrain
    RandomInt randomInt(1, 10);
    for (int i = 0; i < Constants::boardWidth; i++) {
        for (int j = 0; j < Constants::boardHeight; j++) {
            if (randomInt.get() == 1 && !(squares_[i][j]->piece())) {
                squares_[i][j]->setTerrain(new Rock());
            } else {
                squares_[i][j]->setTerrain(new Grass());
            }
            squares_[i][j]->terrain()->setCoordinates(QPoint(i, j));
            addItem(squares_[i][j]->terrain());
        }
    }

    qDebug() << "Constructing consumbles";

    RandomInt randomConsumable = RandomInt(0, ConsumableTypes.size() - 1);
    for (int i = 0; i < Constants::boardWidth; i++) {
        for (int j = 0; j < Constants::boardHeight; j++) {
            if (randomInt.get() == 1 && squares_[i][j]->occupiable()) {
                Consumable* consumable = buildConsumable(ConsumableTypes[randomConsumable.get()]);
                consumable->setCoordinates(QPoint(i, j));
                squares_[i][j]->setConsumable(consumable);
                addItem(consumable);
            }
        }
    }

    playerTurn_ = true;
    updateVision();

}

const std::vector<std::vector<Square*>>& Board::squares() const {
    return squares_;
}

void Board::showSelected() {
    if (!selectedPiece_) {
        selectedMask_.hide();
    } else {
        selectedMask_.setPos(selectedPiece_->coordinates() * Constants::squareSize);
        selectedMask_.show();
    }
}

void Board::showMoves() {
    static std::vector<Square*> occupiableSquares;
    for (auto occupiableSquare: occupiableSquares) {
        occupiableSquare->showOccupiable(false);
    }
    occupiableSquares.clear();
    if (!selectedPiece_ || selectedPiece_->movesLeft() == 0) {
        return;
    }
    for (const auto& move: moves) {
        QPoint newCoord = selectedPiece_->coordinates() + move;
        if (!onBoard(newCoord)) {
            continue;
        }
        Square* newSquare = squares_[newCoord.x()][newCoord.y()];
        if (newSquare->occupiable()) {
            newSquare->showOccupiable(true);
            occupiableSquares.push_back(newSquare);
        }
    }
}

void Board::movePiece(Square* oldSquare, Square* newSquare) {
    qDebug() << "Moving piece from" << oldSquare->coordinates() << "to" << newSquare->coordinates();
    if (!oldSquare->piece() || !newSquare->occupiable() ||
        /*dist(oldSquare->coordinates(), newSquare->coordinates()) != 1 || */
        oldSquare->piece()->movesLeft() == 0) {
        return;
    }
    newSquare->setPiece(oldSquare->piece());
    newSquare->piece()->setCoordinates(newSquare->coordinates(), false);
    newSquare->piece()->moved();
    oldSquare->setPiece(nullptr);
    showSelected();

    qDebug() << "starting move animation";

    QPropertyAnimation *animation = new QPropertyAnimation(newSquare->piece(), "pos");
    animation->setStartValue(oldSquare->pos());
    animation->setEndValue(newSquare->pos());
    animation->setDuration(500);
    animation->start();

    qDebug() << "stopping move animation";





    if (newSquare->consumable()) {
        newSquare->piece()->consume(newSquare->consumable());
        removeItem(newSquare->consumable());
        //delete newSquare->consumable();
        newSquare->setConsumable(nullptr);
        //menu.setText(newSquare->piece()->info());


    }
    setMenu(selectedPiece_);
    updateVision();
    //checkWin();
    update();

}

void Board::showRange(Piece *piece) {
    if (!piece) {
        //qDebug() << "Deleting range";
        rangeIndicator_.hide();
        return;
    }

    //qDebug() << "Showing Range" << piece->coordinates();

    int range = piece->stat("range");

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

    /*
    for (int i = 0; i < points.size(); i++) {
        if (points[i].x() == 0 && points[(i + 1) % points.size()].y() == 0) {
            qDebug() << "inserted";
            points.insert(i + 1, QPointF(0, 0));
        }
    }
    */

    rangeIndicator_.setPolygon(QPolygonF(points));
    rangeIndicator_.show();

    update();

}


void Board::updateVision() {
    qDebug() << "Updating vision";
    for (auto& vec: squares_) {
        for (auto& square: vec) {
            square->setPlayerVision(false);
        }
    }
    for (int i = 0; i < Constants::boardWidth; i++) {
        for (int j = 0; j < Constants::boardHeight; j++) {
            Piece *piece = squares_[i][j]->piece();
            if (piece && piece->playerPiece()) {
                int vision = piece->stat("range");
                for (int x = -vision; x <= vision; x++) {
                    for (int y = -(vision - abs(x)); y <= vision - abs(x); y++) {
                        QPoint visionCoord = piece->coordinates() + QPoint(x, y);
                        if (onBoard(visionCoord) && !squares_[visionCoord.x()][visionCoord.y()]->playerVision() && hasVision(piece->coordinates(), visionCoord)) {
                            squares_[i + x][j + y]->setPlayerVision(true);
                        }
                    }
                }
            }
        }
    }
    update();
}



bool Board::hasVision(QPoint a, QPoint b) {

    //return true;

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

/*
void Board::onPieceHoverEnter(Piece *piece) {
    //qDebug() << "Hover enter" << piece->coordinates();
    if (focusedPiece_) {
        return;
    }
    hoveredPiece_ = piece;
    showRange(piece);
    setMenu(piece);

    update();
}
void Board::onPieceHoverLeave(Piece *piece) {
    //qDebug() << "Hover leave" << piece->coordinates();
    if (focusedPiece_) {
        return;
    }
    hoveredPiece_ = nullptr;
    showRange(nullptr);
    setMenu(nullptr);

    update();

}
*/
bool Board::checkWin() {
    qDebug() << "Checking win";
    if (!king_) {
        qDebug() << "LOST-------------------------------------";
        menu.setText("Lose!");
        Sleep(5000);
        setupBoard(level_);
        return true;
    }
    if (king_->coordinates() == Constants::target1 || king_->coordinates() == Constants::target2) {
        qDebug() << "WON-------------------------------------";
        menu.setText("Win!");
        Sleep(5000);
        setupBoard(++level_);
        return true;
    }
    return false;
}

void Board::onSquareClick(Square *square) {
    //qDebug() << "Clicked square" << square->coordinates();

    if (selectedPiece_ && square->occupiable()) {
        if (QGuiApplication::keyboardModifiers() & 0x04000000 || // 按 control 键后能随意移动一个棋子，用于debugging
            dist(selectedPiece_->coordinates(), square->coordinates()) == 1) {
            movePiece(squares_[selectedPiece_->coordinates().x()][selectedPiece_->coordinates().y()], square);
        }
        if (checkWin()) {
            return;
        }
        showMoves();
    }
    setMenu(square->piece());
    setFocusedPiece(square->piece());
    showSelected();
    update();
}

void Board::onAttackClick() {
    qDebug() << selectedPiece_->coordinates() << "attacking" << focusedPiece_->coordinates();
    selectedPiece_->useAttack(focusedPiece_);
    checkIfDead(focusedPiece_);
    if (checkWin()) {
        return;
    }
    setMenu(focusedPiece_);
}

void Board::onSpellClick() {
    qDebug() << selectedPiece_->coordinates() << "spelling" << focusedPiece_->coordinates();
    selectedPiece_->useSpell(focusedPiece_);
    checkIfDead(focusedPiece_);
    if (checkWin()) {
        return;
    }
    setMenu(focusedPiece_);
}

void Board::checkIfDead(Piece *piece) {
    if (piece->stat("health") <= 0) {

        if (piece == king_) {
            king_ = nullptr;
        }
        squares_[piece->coordinates().x()][piece->coordinates().y()]->setPiece(nullptr);
        removeItem(piece);
        showMoves();
    }
}

void Board::setMenu(Piece *piece) {
    //qDebug() << "Setting menu, player turn" << playerTurn_;
    menu.reset();
    if (playerTurn_) {
        menu.appendText("Your turn\n");
    } else {
        menu.appendText("Enemy's turn\n");
    }
    if (!piece || !playerTurn_) {
        update();
        return;
    }
    menu.appendText(piece->info());
    if (selectedPiece_) {
        if (piece == selectedPiece_) {
            menu.showSkip(true);
        } else if (selectedPiece_->inRange(piece)) {
            if (!piece->playerPiece() && selectedPiece_->canUseAttack()) {
                menu.showAttack(true);
            }
            if (canTarget(piece, selectedPiece_->spell()) && selectedPiece_->canUseSpell()) {
                menu.showSpell(true);
            }
        }
    } else {
        if (piece->playerPiece()) {
            menu.showSelect(true);
        }
    }
    update();
}

bool Board::canTarget(Piece *piece, const Ability& ability) {
    if (ability.target() == TargetType::all) {
        return true;
    }
    if (playerTurn_) {
        return piece->playerPiece() && ability.target() == TargetType::ally ||
              !piece->playerPiece() && ability.target() == TargetType::enemy;
    } else {
        return !piece->playerPiece() && ability.target() == TargetType::ally ||
                piece->playerPiece() && ability.target() == TargetType::enemy;
    }
}

void Board::setFocusedPiece(Piece *piece) {
    focusedPiece_ = piece;
    if (piece) {
        showRange(focusedPiece_);
        setMenu(focusedPiece_);
    }
    update();
}


void Board::onSelectClick() {
    selectedPiece_ = focusedPiece_;
    onSelectChange();

}

void Board::onSkipClick() {
    qDebug() << "Skipping";
    playerTurn_ = !playerTurn_;
    if (selectedPiece_) {
        selectedPiece_->skipped();
    }
    selectedPiece_ = nullptr;
    focusedPiece_ = nullptr;
    onSelectChange();
    if (!playerTurn_) {
        emit aiRun(level_);
    }
}

void Board::onSelectChange() {
    if (playerTurn_) {
        showSelected();
        showMoves();
        showRange(selectedPiece_);
        setMenu(selectedPiece_);
        update();
    }
}

void Board::onViewChange(QPointF map, double scale) {
    menu.setScale(menu.scale() / scale);
    menu.setPos(map);

}
