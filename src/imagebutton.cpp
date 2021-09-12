#include "imagebutton.hpp"

QRectF ImageButton::boundingRect() const {
    return QRectF(0, 0, Constants::buttonSize, Constants::buttonSize);
}

void ImageButton::mousePressEvent(QGraphicsSceneMouseEvent*) {
    emit clicked();
}

ImageButton::ImageButton(const QString& path, QGraphicsItem *parent): QGraphicsItem(parent) {
    setZValue(1);
    QPixmap pix(path);
    pix = pix.scaled(Constants::buttonSize, Constants::buttonSize);
    image_.setPixmap(pix);
}


