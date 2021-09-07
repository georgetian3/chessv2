#include "entity.hpp"

QRectF Entity::boundingRect() const {
    return QRectF(0, 0, Constants::squareSize, Constants::squareSize);
}
void Entity::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, image_);
}
Entity::Entity() {
    setAcceptHoverEvents(true);
    mask_.fill(QColor(0, 255, 0, 100));
}



bool Entity::blocksVision() {
    return blocksVision_;
}

QString Entity::name() const {
    return name_;
}

QString Entity::info() const {
    return name_ + '\n' + description_;
}




QPoint Entity::coordinates() const {
    return coordinates_;
}

void Entity::setCoordinates(const QPoint &coordinates) {
    coordinates_ = coordinates;
    setPos(coordinates_ * Constants::squareSize);
}


