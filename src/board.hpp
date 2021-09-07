#ifndef BOARD_HPP
#define BOARD_HPP

#include "imagebutton.hpp"
#include "rangemarker.hpp"
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
    Piece* selectedPiece = nullptr;

    int dist(Square* a, Square* b) {
        return (a->coordinates() - b->coordinates()).manhattanLength();
    }


    void showMoves(Piece *piece);
    void movePiece(Square* oldSquare, Square* newSquare);
    void updateVision();
    std::vector<Square*> getVisibleSquares(Square *square);
    bool hasVision(Piece *a, Piece *b);

    ImageButton *attackButton;
    ImageButton *abilityButton;
    ImageButton *selectButton;
    ImageButton *skipButton;
    QGraphicsTextItem *infoText;



public:

    Board(QObject *parent = nullptr);
    ~Board();
    void setupBoard();





public slots:

    void onPieceHoverEnter(Piece *piece) {
        hoveredPiece = piece;
        if (!selectedPiece && piece->playerPiece()) {
            selectButton->setCoordinates(piece->coordinates(), CornerType::nw);
            selectButton->show();
        }
        piece->showRange(true);

        //piece->showStats(true);
        if (selectedPiece && !piece->playerPiece() && selectedPiece->inRange(piece)) {
            attackButton->setCoordinates(piece->coordinates());
            attackButton->show();
        }
        update();
    }
    void onPieceHoverLeave(Piece *piece) {
        selectButton->hide();
        attackButton->hide();
        piece->showRange(false);
        //piece->showStats(false);
        update();
    }




    void onSquareClick(Square *square) {
        qDebug() << "Clicked square" << square->coordinates();
        if (selectedPiece && square->occupiable()) {
            movePiece(squares[selectedPiece->coordinates().x()][selectedPiece->coordinates().y()], square);
        }
    }


    void onAttackClick() {
        selectedPiece->attack(hoveredPiece);
    }

    void onAbilityClick() {

    }


    void onSelectClick() {
        qDebug() << "Selected piece" << hoveredPiece->name();
        selectButton->hide();
        selectedPiece = hoveredPiece;
        selectedPiece->showSelected(true);
        skipButton->setCoordinates(selectedPiece->coordinates(), CornerType::nw);
        skipButton->show();
        showMoves(selectedPiece);
        //update();
    }

    void onSkipClick() {
        qDebug() << "Clicked skip";
        playerTurn = false;
        selectedPiece->showSelected(false);
        selectedPiece = nullptr;
        showMoves(nullptr);
        skipButton->hide();
        update();
    }

    void onViewPan(QPoint delta) {
        qDebug() << "View panned by" << delta;
    }



signals:

};

#endif // BOARD_HPP
