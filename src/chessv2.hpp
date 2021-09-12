#ifndef CHESSV2_HPP
#define CHESSV2_HPP

#include "ai.hpp"
#include "board.hpp"
#include <QGraphicsView>
#include <QMediaPlayer>

class ChessV2: public QGraphicsView {

    Q_OBJECT

    AI ai_;
    Board board_;
    QMediaPlayer bgm;

    bool panning_ = false;
    QPoint panStart_;

    void keyPressEvent(QKeyEvent *event);

    // 实现用鼠标滚轮缩放
    void wheelEvent(QWheelEvent *event);

    // 实现使用鼠标拖动棋盘
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:

    ChessV2(QWidget *parent = nullptr);

signals:

    // 让Board知道棋盘的位置或大小变了，所以Board可以调整Menu的位置
    void viewChanged(QPointF, double);

};

#endif // CHESSV2_HPP
