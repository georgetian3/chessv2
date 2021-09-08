#include "entity.hpp"


void Entity::paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) {
    //painter->drawPixmap(0, 0, Constants::squareSize, Constants::squareSize, image_);
}

Entity::Entity(): image_(QGraphicsPixmapItem(this)) {
    //qDebug() << "entity constructor";
    setAcceptHoverEvents(true);
}



bool Entity::blocksVision() {
    return blocksVision_;
}

QString Entity::info() const {
    return name_ + '\n' + description_;
}

void Entity::setImage(const QString &imagePath) {
    image_.setPixmap(QPixmap(imagePath).scaled(Constants::squareSize, Constants::squareSize));
}

QPoint Entity::coordinates() const {
    return coordinates_;
}

void Entity::setCoordinates(const QPoint &coordinates) {
    coordinates_ = coordinates;
    setPos(coordinates_ * Constants::squareSize);
}


