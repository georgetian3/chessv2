#ifndef CHESSV2_HPP
#define CHESSV2_HPP

#include "ai.hpp"
#include "board.hpp"
#include <QGraphicsView>
#include <QMediaPlayer>

class ChessV2: public QGraphicsView {

    Q_OBJECT

    Board board_;
    AI ai_;
    QMediaPlayer bgm;

    bool panning_ = false;
    QPoint panStart_;

    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:

    ChessV2(QWidget *parent = nullptr);

signals:

    void viewChanged(QPointF, double);

};

#endif // CHESSV2_HPP
