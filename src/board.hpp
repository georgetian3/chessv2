#ifndef BOARD_HPP
#define BOARD_HPP

#include "sidepane.hpp"
#include "consumable.hpp"
#include "piece.hpp"
#include "terrain.hpp"
#include "square.hpp"
#include "gamestate.hpp"
#include "randomint.hpp"
#include <QtWidgets>


#include <cmath>
#include <set>
#include <string>
#include <vector>


enum class SideType {north, east, south, west};

class RangeMarker: public QGraphicsLineItem {
public:
    RangeMarker(QPoint position, SideType side, QGraphicsLineItem * parent = 0): QGraphicsLineItem(parent) {
        setPos(position * Constants::squareSize);
        QPen pen;
        pen.setColor(QColor(100, 100, 255));
        pen.setWidth(10);
        setPen(pen);
        switch (side) {
            case SideType::north:
                setLine(0, 0, Constants::squareSize, 0);
                break;
            case SideType::east:
                setLine(Constants::squareSize, 0, Constants::squareSize, Constants::squareSize);
                break;
            case SideType::south:
                setLine(0, Constants::squareSize, Constants::squareSize, Constants::squareSize);
                break;
            case SideType::west:
                setLine(0, 0, 0, Constants::squareSize);
                break;
        }
    }
};

class ImageButton: public QObject, public QGraphicsItem {
    Q_OBJECT
    QPixmap img_;
public:
    ImageButton(const QString& path, QGraphicsItem *parent = nullptr): QGraphicsItem(parent) {
        img_ = QPixmap(path);
        img_ = img_.scaledToHeight(Constants::squareSize / 2, Qt::SmoothTransformation);
    }
    QRectF boundingRect() const override {
        return QRect(0, 0, img_.size().width(), img_.size().height());
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override {
        painter->drawPixmap(0, 0, img_.size().width(), img_.size().height(), img_);
    }

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
        emit clicked();
    }
signals:
    void clicked();
};


class Board: public QGraphicsScene {



    Q_OBJECT

    int movesLeft;
    bool playerTurn = true;

    std::vector<std::vector<Square*>> squares;
    QPixmap bg = QPixmap(":/res/img/bg.jpg");
    Square* focusedSquare;
    Square* selectedSquare;
    ImageButton attackButton = ImageButton(":/res/img/attack.png");
    ImageButton abilityButton = ImageButton(":/res/img/ability.png");
    ImageButton selectButton = ImageButton(":/res/img/select.png");
    ImageButton skipButton = ImageButton(":/res/img/skip.png");

    const std::vector<QPoint> moves = {
        QPoint(0, 1),
        QPoint(0, -1),
        QPoint(1, 0),
        QPoint(-1, 0)
    };



    void updateRange(Square *square = nullptr) {
        static std::vector<RangeMarker*> rangeMarkers;
        for (auto rangeMarker: rangeMarkers) {
            delete rangeMarker;
        }
        rangeMarkers.clear();
        if (!square) {
            return;
        }
        Piece *piece = square->piece();
        if (piece) {
            int range = piece->getStat("range");
            for (int x = -range; x <= range; x++) {
                for (int y:  {-(range - abs(x)), range - abs(x)}) {
                    QPoint rangePos = square->getPos() + QPoint(x, y);
                    if (onBoard(rangePos)) {
                        if (x > 0) {
                            rangeMarkers.push_back(new RangeMarker(rangePos, SideType::east));
                            if (y > 0 || y == 0) {
                                rangeMarkers.push_back(new RangeMarker(rangePos, SideType::south));
                            }
                            if (y < 0 || y == 0) {
                                rangeMarkers.push_back(new RangeMarker(rangePos, SideType::north));
                            }
                        } else if (x < 0) {
                            rangeMarkers.push_back(new RangeMarker(rangePos, SideType::west));
                            if (y > 0 || y == 0) {
                                rangeMarkers.push_back(new RangeMarker(rangePos, SideType::south));
                            }
                            if (y < 0 || y == 0) {
                                rangeMarkers.push_back(new RangeMarker(rangePos, SideType::north));
                            }
                        } else {
                            rangeMarkers.push_back(new RangeMarker(rangePos, SideType::west));
                            rangeMarkers.push_back(new RangeMarker(rangePos, SideType::east));
                            if (y > 0) {
                                rangeMarkers.push_back(new RangeMarker(rangePos, SideType::south));
                            } else {
                                rangeMarkers.push_back(new RangeMarker(rangePos, SideType::north));
                            }

                        }
                    }
                }
            }
            for (const auto& rangeMarker: rangeMarkers) {
                addItem(rangeMarker);
            }
        }
    }


    void highlight(Square *square) {
        static std::vector<Square*> highlighted;
        for (auto highlightedSquare: highlighted) {
            highlightedSquare->highlight(false);
        }
        highlighted.clear();
        if (!square) {
            return;
        }
        for (const auto& move: moves) {
            QPoint newPos = square->getPos() + move;
            if (!onBoard(newPos)) {
                continue;
            }
            Square* newSquare = squares[newPos.x()][newPos.y()];
            if (newSquare->occupiable()) {
                highlighted.push_back(newSquare);
                newSquare->highlight(true);
            }
        }
    }




    bool onBoard(const QPoint& position) {
        return position.x() >= 0 && position.x() < Constants::boardLength
            && position.y() >= 0 && position.y() < Constants::boardWidth;
    }



    void movePiece(Square* oldSquare, Square* newSquare) {
        if ((oldSquare->getPos() - newSquare->getPos()).manhattanLength() == 1) {
            oldSquare->movePieceTo(newSquare);
            updateVision();
            selectPiece(newSquare);
        }

    }



    void updateVision() {
        for (auto& vec: squares) {
            for (auto& square: vec) {
                if (square->playerVision() == VisionType::visible) {
                    square->setPlayerVision(VisionType::seen);
                }
            }
        }
        for (int i = 0; i < Constants::boardLength; i++) {
            for (int j = 0; j < Constants::boardWidth; j++) {
                if (squares[i][j]->piece()) {
                    auto visibleSquares = getVisibleSquares(squares[i][j]);
                    for (auto square: visibleSquares) {
                        square->setPlayerVision(VisionType::visible);
                    }
                }
            }
        }
    }

    std::vector<Square*> getVisibleSquares(Square *square) {
        std::vector<Square*> visibleSquares;
        Piece *piece = square->piece();
        if (piece) {
            int vision = piece->getStat("range");
            for (int x = -vision; x <= vision; x++) {
                for (int y = -(vision - abs(x)); y <= vision - abs(x); y++) {
                    QPoint visionPos = square->getPos() + QPoint(x, y);
                    if (onBoard(visionPos)/* && hasVision(square, squares[visionPos.x()][visionPos.y()])*/) {
                        visibleSquares.push_back(squares[visionPos.x()][visionPos.y()]);
                    }
                }
            }
        }
        return visibleSquares;
    }

    bool hasVision(Square *a, Square *b) {

        double x1 = a->getPos().x();
        double x2 = b->getPos().x();

        double y1 = a->getPos().y();
        double y2 = b->getPos().y();
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

    std::vector<std::vector<PieceType>> playerPiecePositions = {
        {PieceType::pawn, PieceType::pawn, PieceType::pawn, PieceType::pawn,
         PieceType::pawn, PieceType::pawn, PieceType::pawn, PieceType::pawn},
        {PieceType::rook, PieceType::knight, PieceType::bishop, PieceType::queen,
         PieceType::king, PieceType::bishop, PieceType::knight, PieceType::rook}
    };

    std::vector<std::vector<PieceType>> enemyPiecePositions = {
        {PieceType::minion, PieceType::minion, PieceType::minion, PieceType::minion}
    };


public:

    Board(QObject *parent = nullptr): QGraphicsScene(parent) {
        qDebug() << "Board ctor";
        setupBoard();
    }

    void setupBoard() {

        bg = bg.scaledToHeight(Constants::squareSize * Constants::boardWidth + 2000);
        QGraphicsPixmapItem *pix = addPixmap(bg);
        pix->setPos((Constants::totalLength - bg.width()) / 2, (Constants::totalWidth - bg.height()) / 2);

        // constructing squares
        for (int i = 0; i < Constants::boardLength; i++) {
            squares.push_back(std::vector<Square*>());
            for (int j = 0; j < Constants::boardWidth; j++) {
                squares[i].push_back(new Square(QPoint(i, j)));
                squares[i][j]->setPos(i * Constants::squareSize, j * Constants::squareSize);
                connect(squares[i][j], SIGNAL(squareClicked(Square*)), this, SLOT(onSquareClick(Square*)));
                addItem(squares[i][j]);
            }
        }

        // constructing terrain
        RandomInt randomInt(1, 10);
        for (int i = 0; i < Constants::boardLength; i++) {
            for (int j = 0; j < Constants::boardWidth; j++) {
                if (randomInt.get() == 1 &&
                    !(i > Constants::boardLength / 2 - 5 && i <= Constants::boardLength / 2 + 3 &&
                      (j == Constants::boardWidth - 2 || j == Constants::boardWidth - 1))) {
                    squares[i][j]->setTerrain(TerrainType::rock);
                } else {
                    squares[i][j]->setTerrain(TerrainType::grass);
                }
            }
        }

        //constructing pieces

        qDebug() << "Constructing pieces";

        int xOffset = (Constants::boardLength - playerPiecePositions[0].size()) / 2;
        int yOffset = Constants::boardWidth - playerPiecePositions.size();
        for (int x = 0; x < playerPiecePositions[0].size(); x++) {
            for (int y = 0; y < playerPiecePositions.size(); y++) {
                squares[x + xOffset][y + yOffset]->setPiece(playerPiecePositions[y][x]);
            }
        }

        xOffset = (Constants::boardLength - enemyPiecePositions[0].size()) / 2;
        for (int x = 0; x < enemyPiecePositions[0].size(); x++) {
            for (int y = enemyPiecePositions.size() - 1; y >= 0 ; y--) {
                squares[x + xOffset][y]->setPiece(enemyPiecePositions[y][x]);
            }
        }

        connect(&attackButton, SIGNAL(clicked()), this, SLOT(onAttackClick()));
        connect(&abilityButton, SIGNAL(clicked()), this, SLOT(onAbilityClick()));
        connect(&selectButton, SIGNAL(clicked()), this, SLOT(onSelectClick()));
        connect(&skipButton, SIGNAL(clicked()), this, SLOT(onSkipClick()));


        updateVision();

        qDebug() << "Finished setupBoard";

    }



    void selectPiece(Square* square) {
        selectedSquare = square;
        focusedSquare = nullptr;
        highlight(square);
        updateRange(square);
    }
    void focusSquare(Square* square) {
        selectedSquare = nullptr;
        focusedSquare = square;
        highlight(nullptr);
        updateRange(square);
    }
    void showActions(Square* square) {
        if (!square || !square->piece()) {
            qDebug() << "Removing buttons";
            removeItem(&attackButton);
            removeItem(&abilityButton);
            return;
        }
        qDebug() << "Adding buttons";
        qDebug() << square->getPos();
        attackButton.setPos((square->getPos() + QPoint(0, 1)) * Constants::squareSize -
                            QPointF(attackButton.boundingRect().width() / 2, attackButton.boundingRect().height() / 2));
        abilityButton.setPos((square->getPos() + QPoint(1, 1)) * Constants::squareSize -
                             QPointF(abilityButton.boundingRect().width() / 2, abilityButton.boundingRect().height() / 2));
        addItem(&attackButton);
        addItem(&abilityButton);

    }

    void attack() {
        ;
    }

    void ability() {
        ;
    }




public slots:
    void onSquareClick(Square *square) {

        if (square->piece()) {
            qDebug() << "Clicked piece";

            if (focusedSquare != square) {
                focusSquare(square);
                emit pieceClicked(square->piece());
            } else {
                selectPiece(square);
            }
        } else if (square->highlighted()) {
            qDebug() << "Clicked highlight";

            movePiece(selectedSquare, square);

        } else {
            focusSquare(square);
        }
        showActions(square);
        update();
    }

    void onSelectClick() {

    }

    void onAttackClick() {

    }

    void onAbilityClick() {

    }

signals:

    void pieceClicked(Piece*);
    void consumableClicked(Consumable*);

};

#endif // BOARD_HPP
