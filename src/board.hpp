#ifndef BOARD_HPP
#define BOARD_HPP

#include "ai.hpp"
#include "menu.hpp"
#include "imagebutton.hpp"
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

class AI;

class Board: public QGraphicsScene {
    Q_OBJECT

    //QPixmap background_ = QPixmap();
    QGraphicsPixmapItem background_;



    const std::vector<std::vector<PieceType>> playerPiecePositions = {
        {PieceType::pawn, PieceType::pawn, PieceType::pawn, PieceType::pawn,
         PieceType::pawn, PieceType::pawn, PieceType::pawn, PieceType::pawn},
        {PieceType::rook, PieceType::knight, PieceType::bishop, PieceType::queen,
         PieceType::king, PieceType::bishop, PieceType::knight, PieceType::rook}
    };
    const std::vector<std::vector<PieceType>> enemyPiecePositions = {
        {PieceType::minion, PieceType::minion, PieceType::minion, PieceType::minion,
         PieceType::minion, PieceType::minion, PieceType::minion, PieceType::minion}
    };
    const std::vector<QPoint> moves = {
        QPoint(0, 1),
        QPoint(0, -1),
        QPoint(1, 0),
        QPoint(-1, 0)
    };

    bool playerTurn_ = true;

    std::vector<std::vector<Square*>> squares_;

    Piece* hoveredPiece_ = nullptr;
    Piece* focusedPiece_ = nullptr;
    Piece* selectedPiece_ = nullptr;
    Piece* king_ = nullptr;

    QGraphicsPolygonItem rangeIndicator_;
    QGraphicsPixmapItem selectedMask_;

    Menu menu;


    int dist(QPoint a, QPoint b);

    void showRange(Piece *piece);
    void showMoves();
    void movePiece(Square* oldSquare, Square* newSquare);
    void updateVision();
    void checkIfDead(Piece *piece);
    std::vector<Square*> getVisibleSquares(Square *square);
    bool hasVision(QPoint a, QPoint b);
    int level_ = 1;

    void initialSetup();
    bool checkWin();
    void showSelected();
    bool canTarget(Piece *piece, const Ability& ability);

    void setMenu(Piece *piece);
    void setFocusedPiece(Piece *piece);
    void onSelectChange();

public:

    Board(QObject *parent = nullptr);
    ~Board();
    void setupBoard(int level);
    const std::vector<std::vector<Square*>>& squares() const;


private slots:
    void onViewChange(QPointF map, double scale);
    void onPieceHoverEnter(Piece *piece);
    void onPieceHoverLeave(Piece *piece);

public slots:

    void onPieceClick(Piece *piece);

    void onSquareClick(Square *square);
    void onAttackClick();
    void onSpellClick();
    void onSelectClick();
    void onSkipClick();





signals:

    void aiRun(int);

};

#endif // BOARD_HPP
