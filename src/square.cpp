#include "square.hpp"



Square::Square(QPoint coordinates, QGraphicsItem *parent): coordinates_(coordinates), QGraphicsItem(parent) {

    setAcceptHoverEvents(true);

    setZValue(20);

    QPixmap pix(Constants::squareSize, Constants::squareSize);

    pix.fill(QColor(255, 0, 0, 100));
    moveMask_.setPixmap(pix);
    moveMask_.hide();

    if (true) {
        pix.fill(QColor(0, 0, 0, 200));
        unseenMask_.setPixmap(pix);
    }

    setPlayerVision(false);


    setPos(coordinates_ * Constants::squareSize);


}

QRectF Square::boundingRect() const {
    return Constants::squareRect;
}

void Square::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    if (playerVision_) {
        QGraphicsItem::hoverEnterEvent(event);
    }
}

void Square::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //qDebug() << "Clicked square" << coordinates_;
    emit squareClicked(this);
}


void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if (moveMask_.isVisible()) {
        //painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, moveMask_.pixmap());
    }
}



QPoint Square::coordinates() const {
    return coordinates_;
}

/*
void Square::setCoordinates(const QPoint& coordinates) {
    coordinates_ = coordinates;
    setPos(coordinates * Constants::squareSize);
}
*/

bool Square::playerVision() const {
    return playerVision_;
}
void Square::setPlayerVision(bool vision) {
    playerVision_ = vision;
    unseenMask_.setVisible(!vision);
}



bool Square::occupiable() const  {
    return !piece_ && terrain_->occupiable();
}
void Square::showOccupiable(int show) {
    moveMask_.setVisible(show);
    update();
}

bool Square::blocksVision() const {
    return (terrain_ ? terrain_->blocksVision() : false) || false &&
           (piece_ ? piece_->blocksVision() : false);
}
void Square::setTerrain(Terrain *terrain) {
    if (terrain_ && terrain) {
        return;
    }
    terrain_ = terrain;

}
Terrain* Square::terrain() const {
    return terrain_;
}


void Square::setPiece(Piece *piece) {
    if (piece_ && piece) {
        return;
    }
    piece_ = piece;


}
Piece* Square::piece() const {
    return piece_;
}

void Square::setConsumable(Consumable *consumable) {
    consumable_ = consumable;
}
Consumable* Square::consumable() const {
    return consumable_;
}
