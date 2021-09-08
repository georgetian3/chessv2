#ifndef CHESSV2_HPP
#define CHESSV2_HPP

#include "board.hpp"
#include "gamestate.hpp"
#include "menu.hpp"
#include <QtWidgets>
#include <QMediaPlayer>

class ChessV2: public QGraphicsView {

    Q_OBJECT

    Board *board = nullptr;
    QMediaPlayer *bgm = nullptr;

public:

    ChessV2(QWidget *parent = nullptr): QGraphicsView(parent) {
        //bgm = new QMediaPlayer;
        //bgm->setMedia(QUrl("qrc:res/audio/bgm.mp3"));
        //bgm->play();

        qDebug() << "ChessV2 ctor";

        setWindowState(Qt::WindowMaximized);

        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



        board = new Board();
        setScene(board);

        connect(this, SIGNAL(viewChanged(QPointF, double)), board, SLOT(onViewChange(QPointF, double)));





        //fitInView(QRectF(0, 0, Constants::totalWidth, Constants::totalHeight), Qt::KeepAspectRatio);



    }




    void keyPressEvent(QKeyEvent *event) {
        switch (event->key()) {
            case Qt::Key_F12: // toggle fullscreen
                qDebug() << "F12";
                setWindowState(windowState() == Qt::WindowFullScreen ? Qt::WindowNoState : Qt::WindowFullScreen);
                break;
            case Qt::Key_Escape: // toggle menu
                //menu->setVisible(!menu->isVisible());
                break;
            default:
                QGraphicsView::keyPressEvent(event);
        }
    }

    void wheelEvent(QWheelEvent *event) {

        double currentScale = transform().m11();
        int angle = event->angleDelta().y();
        double factor;

        if (angle >= 0 /*&& currentScale < 4*/) {
            factor = 1.2;
        } else if (angle < 0 /*&& currentScale > 0.25*/) {
            factor = 0.8;
        } else {
            return;
        }

        const ViewportAnchor anchor = transformationAnchor();
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        scale(factor, factor);
        setTransformationAnchor(anchor);

        emit viewChanged(mapToScene(10, 10), factor);
    }

    bool panning_ = false;
    QPoint panStart_;

    void mousePressEvent(QMouseEvent *event) {
        panning_ = true;
        panStart_ = event->pos();
        QGraphicsView::mousePressEvent(event);

    }

    void mouseMoveEvent(QMouseEvent *event) {
        if (panning_) {
            QPoint delta = event->pos() - panStart_;
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
            panStart_ = event->pos();

            emit viewChanged(mapToScene(10, 10), 1);
        }
        QGraphicsView::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) {
        panning_ = false;
        QGraphicsView::mouseReleaseEvent(event);
    }

signals:

    void viewChanged(QPointF, double);

};

#endif // CHESSV2_HPP
