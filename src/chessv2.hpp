#ifndef CHESSV2_HPP
#define CHESSV2_HPP

#include "sidepane.hpp"
#include "board.hpp"
#include "gamestate.hpp"
#include "menu.hpp"
#include <QtWidgets>

class ChessV2: public QGraphicsView {

    Board *board = nullptr;
    SidePane *sidepane = nullptr;

public:

    ChessV2(QWidget *parent = nullptr): QGraphicsView(parent) {

        qDebug() << "ChessV2 ctor";

        setWindowState(Qt::WindowMaximized);

        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        sidepane = new SidePane();
        sidepane->setText("test");


        board = new Board();
        setScene(board);

        fitInView(QRectF(0, 0, Constants::totalLength, Constants::totalWidth), Qt::KeepAspectRatio);

        setDragMode(QGraphicsView::ScrollHandDrag);


    }


    void scrollContentsBy(int dx, int dy) {
        scene()->invalidate();
        QGraphicsView::scrollContentsBy(dx, dy);
    }


    void drawForeground(QPainter *painter, const QRectF &rect) {
        painter->resetTransform();
        sidepane->render(painter, sidepane->itemsBoundingRect());
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
        } else if (angle < 0 /*&& currentScale > 0.2*/) {
            factor = 0.8;
        } else {
            return;
        }

        const ViewportAnchor anchor = transformationAnchor();
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        scale(factor, factor);
        setTransformationAnchor(anchor);
    }
};

#endif // CHESSV2_HPP
