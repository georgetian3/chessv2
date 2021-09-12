#include "chessv2.hpp"

ChessV2::ChessV2(QWidget *parent): QGraphicsView(parent), ai_(board_.squares()) {

    //qDebug() << "ChessV2 ctor";

    bgm.setMedia(QUrl("qrc:res/audio/bgm.mp3"));
    bgm.play();

    setWindowState(Qt::WindowMaximized);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setScene(&board_);

    connect(this, SIGNAL(viewChanged(QPointF, double)), &board_, SLOT(onViewChange(QPointF, double)));
    connect(&board_, SIGNAL(aiRun(int)), &ai_, SLOT(run(int)));

    connect(&ai_, SIGNAL(squareClicked(Square*)), &board_, SLOT(onSquareClick(Square*)));
    connect(&ai_, SIGNAL(attackClicked()), &board_, SLOT(onAttackClick()));
    connect(&ai_, SIGNAL(spellClicked()), &board_, SLOT(onSpellClick()));
    connect(&ai_, SIGNAL(selectClicked()), &board_, SLOT(onSelectClick()));
    connect(&ai_, SIGNAL(skipClicked()), &board_, SLOT(onSkipClick()));


    //fitInView(QRectF(0, 0, Constants::totalWidth, Constants::totalHeight), Qt::KeepAspectRatio);



}




void ChessV2::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case Qt::Key_F12: // 全屏
            setWindowState(windowState() == Qt::WindowFullScreen ? Qt::WindowNoState : Qt::WindowFullScreen);
            break;
        default:
            QGraphicsView::keyPressEvent(event);
    }
}

void ChessV2::wheelEvent(QWheelEvent *event) {

    int angle = event->angleDelta().y();
    double factor;

    if (angle >= 0 && transform().m11() < 3) {
        factor = 1.2;
    } else if (angle < 0 && transform().m11() > 0.5) {
        factor = 0.8;
    } else {
        return;
    }

    const ViewportAnchor anchor = transformationAnchor();
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    scale(factor, factor);
    setTransformationAnchor(anchor);

    emit viewChanged(mapToScene(0, 0), factor);
}


void ChessV2::mousePressEvent(QMouseEvent *event) {
    panning_ = true;
    panStart_ = event->pos();
    QGraphicsView::mousePressEvent(event);

}

void ChessV2::mouseMoveEvent(QMouseEvent *event) {
    if (panning_) {
        QPoint delta = event->pos() - panStart_;
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
        verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
        panStart_ = event->pos();

        emit viewChanged(mapToScene(0, 0), 1);
    }
    QGraphicsView::mouseMoveEvent(event);
}

void ChessV2::mouseReleaseEvent(QMouseEvent *event) {
    panning_ = false;
    QGraphicsView::mouseReleaseEvent(event);
}

