#ifndef CHESSV2_HPP
#define CHESSV2_HPP

#include "board.hpp"
#include "gamestate.hpp"
#include "menu.hpp"
#include <QtWidgets>

class ChessV2: public QGraphicsView {

    Menu *menu = nullptr;
    Board *board = nullptr;
    QHBoxLayout *hBox = nullptr;
    QGraphicsScene *scene = nullptr;

public:

    ChessV2(QWidget *parent = nullptr): QGraphicsView(parent) {

        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

        scene = new QGraphicsScene(this);
        setScene(scene);


        Board *board = new Board();

        scene->addItem(board);

        setDragMode(QGraphicsView::ScrollHandDrag);




    }

    void keyPressEvent(QKeyEvent *event) {
        switch (event->key()) {
            case Qt::Key_F12: // toggle fullscreen
                setWindowState(windowState() == Qt::WindowFullScreen ? Qt::WindowNoState : Qt::WindowFullScreen);
                break;
            case Qt::Key_Escape: // toggle menu
                //menu->setVisible(!menu->isVisible());
                break;
            default:
                qDebug() << "Default";
                QWidget::keyPressEvent(event);
        }
    }

    void wheelEvent(QWheelEvent *event) {

        double currentScale = transform().m11();
        int angle = event->angleDelta().y();
        double factor;

        if (angle >= 0 && currentScale < 4) {
            factor = 1.2;
        } else if (angle < 0 && currentScale > 0.2) {
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
