#ifndef BOARD_HPP
#define BOARD_HPP

#include "menu.hpp"
#include "imagebutton.hpp"
#include "rangemarker.hpp"
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


    QPixmap background_ = QPixmap(":/res/img/bg.jpg");


    const std::vector<std::vector<PieceType>> playerPiecePositions = {
        {PieceType::pawn, PieceType::pawn, PieceType::pawn, PieceType::pawn,
         PieceType::pawn, PieceType::pawn, PieceType::pawn, PieceType::pawn},
        {PieceType::rook, PieceType::knight, PieceType::bishop, PieceType::queen,
         PieceType::king, PieceType::bishop, PieceType::knight, PieceType::rook}
    };
    const std::vector<std::vector<PieceType>> enemyPiecePositions = {
        {PieceType::minion, PieceType::minion, PieceType::minion, PieceType::minion},
        {PieceType::minion, PieceType::minion, PieceType::minion, PieceType::minion},
        {PieceType::minion, PieceType::minion, PieceType::minion, PieceType::minion},
        {PieceType::minion, PieceType::minion, PieceType::minion, PieceType::minion},
        {PieceType::minion, PieceType::minion, PieceType::minion, PieceType::minion},
        {PieceType::minion, PieceType::minion, PieceType::minion, PieceType::minion}
    };
    const std::vector<QPoint> moves = {
        QPoint(0, 1),
        QPoint(0, -1),
        QPoint(1, 0),
        QPoint(-1, 0)
    };

    int movesLeft;
    bool playerTurn = true;

    std::vector<std::vector<Square*>> squares;

    Piece* hoveredPiece = nullptr;
    Piece* focusedPiece = nullptr;
    Piece* selectedPiece = nullptr;

    int dist(Square* a, Square* b) {
        return (a->coordinates() - b->coordinates()).manhattanLength();
    }

    void showRange(Piece *piece);
    void showMoves();
    void movePiece(Square* oldSquare, Square* newSquare);
    void updateVision();
    std::vector<Square*> getVisibleSquares(Square *square);
    bool hasVision(QPoint a, QPoint b);
    QGraphicsPolygonItem rangeIndicator;

    QGraphicsPixmapItem selectedMask_;

    Menu menu;

    void showSelected();

public:

    Board(QObject *parent = nullptr);
    ~Board();
    void setupBoard();





public slots:

    void onPieceClick(Piece *piece) {

    }

    void onPieceHoverEnter(Piece *piece) {

        //qDebug() << "Hover enter" << piece->name();
        hoveredPiece = piece;
        if (focusedPiece) {
            return;
        }

        showRange(piece);
        menu.setText(piece->info());
        setMenu(squares[piece->coordinates().x()][piece->coordinates().y()]);
        /*
        if (selectedPiece) {
            if (piece == selectedPiece) {
                menu.showSkip(true);
            } else if (!piece->playerPiece() && selectedPiece->inRange(piece)) {
                menu.showAttack(true);
            }
        } else {
            if (piece->playerPiece()) {
                menu.showSelect(true);
            }
        }
        */


        update();
    }
    void onPieceHoverLeave(Piece *piece) {
        //qDebug() << "Hover leave";
        if (focusedPiece) {
            return;
        }
        menu.reset();

        showRange(nullptr);

        update();

    }


    void onSquareClick(Square *square) {
        qDebug() << "Clicked square" << square->coordinates();

        if (selectedPiece && square->occupiable()) {
            movePiece(squares[selectedPiece->coordinates().x()][selectedPiece->coordinates().y()], square);
            showMoves();
        }
        setMenu(square);
        setFocusedPiece(square->piece());
        showSelected();
        update();
    }


    void onAttackClick() {
        selectedPiece->useAttack(focusedPiece);
        menu.setText(focusedPiece->info());
    }

    void onAbilityClick() {
        selectedPiece->useSpell(focusedPiece);
        menu.setText(focusedPiece->info());
    }

    void setMenu(Square *square) {
        menu.reset();
        if (!square->piece()) {
            return;
        }
        menu.setText(square->piece()->info());
        if (selectedPiece) {
            if (square->piece() == selectedPiece) {
                menu.showSkip(true);
            } else if (!square->piece()->playerPiece() && selectedPiece->inRange(square->piece())) {
                menu.showAttack(true);
            }
        } else {
            if (square->piece()->playerPiece()) {
                menu.showSelect(true);
            }
        }
    }

    void setFocusedPiece(Piece *piece) {
        focusedPiece = piece;
        if (piece) {
            showRange(focusedPiece);
            menu.setText(focusedPiece->info());
        }
        update();
    }


    void onSelectClick() {
        selectedPiece = focusedPiece;
        onSelectChange();

    }

    void onSkipClick() {
        selectedPiece = nullptr;
        onSelectChange();
    }

    void onSelectChange() {
        showSelected();
        showMoves();
        if (selectedPiece) {
            setMenu(squares[selectedPiece->coordinates().x()][selectedPiece->coordinates().y()]);
        }
        //playerTurn = false;

        update();
    }

    void onViewChange(QPointF map, double scale) {
        menu.setScale(menu.scale() / scale);
        menu.setPos(map);

    }



signals:

};

#endif // BOARD_HPP
