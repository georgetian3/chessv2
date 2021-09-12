#include "entity.hpp"

Entity::Entity() {
    setAcceptHoverEvents(true);
}

QRectF Entity::boundingRect() const {
    return Constants::squareRect;
}

bool Entity::occupiable() const {
    return occupiable_;
}

bool Entity::blocksVision() const {
    return blocksVision_;
}

QString Entity::info() const {
    return name_;
}

void Entity::setImage(const QString &imagePath) {
    image_.setPixmap(QPixmap(imagePath).scaled(Constants::squareSize, Constants::squareSize));
}

QPoint Entity::coordinates() const {
    return coordinates_;
}

void Entity::setCoordinates(const QPoint &coordinates, bool callSetPos) {
    coordinates_ = coordinates;
    if (callSetPos) {
        setPos(coordinates_ * Constants::squareSize);
    }

}


