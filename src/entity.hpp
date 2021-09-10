#ifndef ENTITY_H
#define ENTITY_H

#include "constants.hpp"
#include <QtWidgets>

class Entity: public QObject, public QGraphicsItem {
    Q_OBJECT

protected:

    QGraphicsPixmapItem image_;

    bool blocksVision_ = false;
    QPoint coordinates_;

    QString name_;
    QString description_;
    QString sound;
    QString info_;
    int z_;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override;
    QRectF boundingRect() const override {
        return QRectF(0, 0, Constants::squareSize, Constants::squareSize);
    }

public:

    Entity();

    void setImage(const QString& imagePath = ":/res/img/placeholder.png");
    bool blocksVision();
    QString info() const;
    QPoint coordinates() const;
    void setCoordinates(const QPoint& coordinates, bool callSetPos = true);


signals:

};




#endif // ENTITY_H
