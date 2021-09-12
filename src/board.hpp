#ifndef BOARD_HPP
#define BOARD_HPP

#include "ai.hpp"
#include "menu.hpp"
#include "imagebutton.hpp"
#include "consumable.hpp"
#include "piece.hpp"
#include "terrain.hpp"
#include "square.hpp"
#include "randomint.hpp"
#include <QtWidgets>


#include <cmath>
#include <set>
#include <string>
#include <vector>

class AI;

class Board: public QGraphicsScene {

    Q_OBJECT


    QGraphicsPixmapItem background_;

    // 我方和敌方的棋子的位置
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


    // 上下左右的移动
    const std::vector<QPoint> moves = {
        QPoint(0, 1),
        QPoint(0, -1),
        QPoint(1, 0),
        QPoint(-1, 0)
    };

    bool playerTurn_ = true;

    std::vector<std::vector<Square*>> squares_;

    //Piece* hoveredPiece_ = nullptr;
    Piece* focusedPiece_ = nullptr;
    Piece* selectedPiece_ = nullptr;
    Piece* king_ = nullptr;

    QGraphicsPolygonItem rangeIndicator_;
    QGraphicsPixmapItem selectedMask_;

    Menu menu;

    // 显示表示视野范围的蓝色线
    void showRange(Piece *piece);
    // 显示表示能走的步骤
    void showMoves();
    // 移动一个棋子
    void movePiece(Square* oldSquare, Square* newSquare);

    // 更新用户的视野
    void updateVision();
    // 判断a和b的中点的连线是否经过遮挡视野的方格
    bool hasVision(QPoint a, QPoint b);
    int level_ = 1;

    // 一次性地创造方格和菜单
    void initialSetup();
    // 判断棋子是否死了，然后做对应的处理
    void checkIfDead(Piece *piece);
    // 判断我方和敌方是否赢了，然后做对应的处理
    bool checkWin();
    // 高亮被选中的棋子
    void showSelected();
    // 判断一个技能能否用在一个棋子上
    bool canTarget(Piece *piece, const Ability& ability);


    void setMenu(Piece *piece);
    void setFocusedPiece(Piece *piece);
    void onSelectChange();

public:

    Board(QObject *parent = nullptr);
    ~Board();
    // 根据级别创建对应的敌方兵的数目
    void setupBoard(int level);
    const std::vector<std::vector<Square*>>& squares() const;


private slots:

    // 用于将菜单“浮”在界面上
    void onViewChange(QPointF map, double scale);
    //void onPieceHoverEnter(Piece *piece);
    //void onPieceHoverLeave(Piece *piece);

public slots:

    void onSquareClick(Square *square);
    void onAttackClick();
    void onSpellClick();
    void onSelectClick();
    void onSkipClick();

signals:

    void aiRun(int);

};

#endif // BOARD_HPP
