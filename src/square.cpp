#include "square.hpp"



Square::Square(QPoint coordinates, QGraphicsItem *parent): coordinates_(coordinates), QGraphicsItem(parent) {
    setPos(coordinates_ * Constants::squareSize);
    moveMask.fill(QColor(255, 0, 0, 100));
    fogMask.fill(QColor(0, 0, 0, 100));
    setZValue(1);
}

void Square::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    //qDebug() << "Clicked square" << position_.x() << position_.y();
    emit squareClicked(this);
    QGraphicsItem::mousePressEvent(event);
}

QRectF Square::boundingRect() const {
    return QRectF(0, 0, Constants::squareSize, Constants::squareSize);
}

void Square::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {
    if (playerVision_ == VisionType::unseen) {
        painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, fog);
        return;
    } else if (playerVision_ == VisionType::seen) {
        painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, fogMask);
    }
    if (showOccupiable_) {
        painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, moveMask);
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
}



bool Square::occupiable() const  {
    qDebug() << "Square" << coordinates_ << !piece_ << terrain_->occupiable();
    return !piece_ && terrain_->occupiable();
}
void Square::showOccupiable(int show) {
    showOccupiable_ = show;
    update();
}

bool Square::blocksVision() const {
    return blocksVision_;
}
void Square::setTerrain(Terrain *terrain) {
    if (terrain_ && terrain) {
        return;
    }
    terrain_ = terrain;

    updateBlocksVision();

}
Terrain* Square::terrain() const {
    return terrain_;
}

void Square::updateBlocksVision() {
    blocksVision_ =
        (terrain_ ? terrain_->blocksVision() : false) ||
        (piece_ ? piece_->blocksVision() : false);
}

void Square::setPiece(Piece *piece) {
    if (piece_ && piece) {
        return;
    }
    piece_ = piece;



    updateBlocksVision();

}
Piece* Square::piece() const {
    return piece_;
}
