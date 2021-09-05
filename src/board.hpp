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


class Board: public QGraphicsScene {

    Q_OBJECT
public:
    std::vector<std::vector<Square*>> squares;
    QPixmap bg = QPixmap(":/res/img/bg.jpg");



    Board(QObject *parent = nullptr): QGraphicsScene(parent) {
        qDebug() << "Board ctor";


        setupBoard();

    }

    void setupBoard() {

        bg = bg.scaledToHeight(Constants::squareSize * Constants::boardWidth + 2000);

        QGraphicsPixmapItem *pix = addPixmap(bg);

        pix->setPos((Constants::totalLength - bg.width()) / 2, (Constants::totalWidth - bg.height()) / 2);


        for (int i = 0; i < Constants::boardLength; i++) {
            squares.push_back(std::vector<Square*>());
            for (int j = 0; j < Constants::boardWidth; j++) {
                squares[i].push_back(new Square(QPoint(i, j)));
                squares[i][j]->setPos(i * Constants::squareSize, j * Constants::squareSize);
                connect(squares[i][j], SIGNAL(squareClicked(Square*)), this, SLOT(onSquareClick(Square*)));
                addItem(squares[i][j]);
            }
        }


        RandomInt randomInt(1, 10);
        for (int i = 0; i < Constants::boardLength; i++) {
            for (int j = 0; j < Constants::boardWidth; j++) {
                if (randomInt.get() == 1) {
                    squares[i][j]->setTerrain(TerrainType::rock);
                } else {
                    squares[i][j]->setTerrain(TerrainType::grass);
                }

            }
        }

        int x = Constants::boardLength / 2 - 4;
        int y = Constants::boardWidth - 2;
        for (int i = 0; i < 8; i++) {
            squares[x + i][y]->setPiece(PieceType::pawn);
        }
        y = Constants::boardWidth - 1;
        x = Constants::boardLength / 2;
        for (int i: {-4, 3}) {
            squares[x + i][y]->setPiece(PieceType::rook);
        }
        for (int i: {-3, 2}) {
            squares[x + i][y]->setPiece(PieceType::knight);
        }
        for (int i: {-2, 1}) {
            squares[x + i][y]->setPiece(PieceType::bishop);
        }

        squares[x - 1][y]->setPiece(PieceType::queen);
        squares[x][y]->setPiece(PieceType::king);

    }


    std::vector<std::vector<int>> moves = {
        {0, 1},
        {0, -1},
        {1, 0},
        {-1, 0}
    };

    std::vector<Square*> showedMoves;


    void hideMoves() {
        for (auto& square: showedMoves) {
            square->setMovable(false);
        }
        showedMoves.clear();
    }


    void showMoves(Square *square) {
        hideMoves();
        for (const auto& move: moves) {
            int newX = square->getPos().x + move[0];
            int newY = square->getPos().y + move[1];
            if (newX < 0 || newY < 0 || newX > Constants::boardLength - 1 || newY > Constants::boardWidth - 1) {
                continue;
            }
            if (!squares[newX][newY]->getPiece()) {
                showedMoves.push_back(squares[newX][newY]);
                squares[newX][newY]->setMovable(true);
            }
        }
    }

    Square *selectedSquare = nullptr;

public slots:

    void onSquareClick(Square *square) {

        if (square->getPiece()) {
            showMoves(square);
        } else if (square->movable()) {
            movePiece(selectedSquare, square);
        } else {
            hideMoves();
        }
        update();

        selectedSquare = square;
    }

    void movePiece(Square* oldSquare, Square* newSquare) {
        //qDebug() << "moving" << oldX << oldY << "to" << newX << newY;
        oldSquare->movePieceTo(newSquare);
        hideMoves();
        selectedSquare = nullptr;
        update();
    }

    void setVision() {
        for (auto& vec: squares) {
            for (auto& square: vec) {
                if (square->playerVision() == 2) {
                    square->setPlayerVision(1);
                }
            }
        }
        for (int i = 0; i < Constants::boardLength; i++) {
            for (int j = 0; j < Constants::boardWidth; j++) {
                if (squares[i][j]->hasPiece()) {
                    //std::vector<Position> pos = visibleSquares(i, j, squares[i][j]->piece->stats["vision"]);
                    for (int k = 0; k < pos.size(); k++) {
                        squares[pos[k][0]][pos[k][1]]->playerVision() = 2;
                    }
                }
            }
        }
    }

    std::vector<Square*> visibleSquares(Square *square) {
        std::vector<std::vector<int>> pos;
        for (; radius >= 0; radius--) {

        }
    }

    double getY(double x, double m, double c) {
        return m * x + c;
    }
    double getX(double y, double m, double c) {
        return (y - c) / m;
    }

    bool hasVision(Square *a, Square *b) {
        double m = (y2 - y1) / (x2 - x1);
        double c = y1 - x1 * m;
        if (abs(m) >= 1) {
            for (int y = y1 + 0.5; y < y2; y += 1) {
                double x = getX(y, m, c);
                double decimal = x - int(x);
                if (abs(decimal - 0.5) < 0.000000001) {
                    if (!(squares[x][y]->terrain->isOccupiable() &&
                          squares[x][y + 1]->terrain->isOccupiable() &&
                          squares[x + 1][y]->terrain->isOccupiable() &&
                          squares[x + 1][y + 1]->terrain->isOccupiable())){
                        return false;
                    }
                } else {
                    if (!(squares[round(x)][y]->terrain->isOccupiable() &&
                          squares[round(x)][y + 1]->terrain->isOccupiable())) {
                         return false;
                    }
                }
            }
        } else {
            for (int x = x1 + 0.5; x < x2; x += 1) {
                double y = getY(x, m, c);
                double decimal = y - int(y);
                if (abs(decimal - 0.5) < 0.000000001) {
                    if (!(squares[x][y]->terrain->isOccupiable() &&
                          squares[x][y + 1]->terrain->isOccupiable() &&
                          squares[x + 1][y]->terrain->isOccupiable() &&
                          squares[x + 1][y + 1]->terrain->isOccupiable())){
                        return false;
                    }
                } else {
                    if (!(squares[x][round(y)]->terrain->isOccupiable() &&
                          squares[x + 1][round(y)]->terrain->isOccupiable())) {
                         return false;
                    }
                }
            }
        }

        return true;

    }

signals:



};

#endif // BOARD_HPP
