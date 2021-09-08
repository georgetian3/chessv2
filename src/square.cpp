#include "square.hpp"



Square::Square(QPoint coordinates, QGraphicsItem *parent): coordinates_(coordinates), QGraphicsItem(parent)

{

    setZValue(2);

    QPixmap pix(Constants::squareSize, Constants::squareSize);

    pix.fill(QColor(255, 0, 0, 100));
    moveMask_.setPixmap(pix);
    moveMask_.hide();

    pix.fill(QColor(0, 0, 0, 100));
    seenMask_.setPixmap(pix);

    setPlayerVision(VisionType::unseen);


    setPos(coordinates_ * Constants::squareSize);


}

void Square::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //qDebug() << "Clicked square" << coordinates_;
    emit squareClicked(this);
    QGraphicsItem::mousePressEvent(event);
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

VisionType Square::playerVision() const {
    return playerVision_;
}
void Square::setPlayerVision(VisionType visionType) {
    playerVision_ = visionType;
    unseenMask_.hide();
    seenMask_.hide();
    if (visionType == VisionType::unseen) {
        unseenMask_.show();
    } else if (visionType == VisionType::seen) {
        seenMask_.show();
    }
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
    if (consumable_ && consumable) {
        return;
    }
    consumable_ = consumable;


}
Consumable* Square::consumable() const {
    return consumable_;
}
