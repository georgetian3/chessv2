#ifndef ENTITY_H
#define ENTITY_H

#include "constants.hpp"
#include <QtWidgets>

class Entity: public QObject, public QGraphicsItem {
    Q_OBJECT

protected:

    QGraphicsPixmapItem image_;

    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    QPoint coordinates_;
    bool blocksVision_ = false;
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
    void setCoordinates(const QPoint& coordinates);


signals:

    void entityClicked(Entity*);


};




#endif // ENTITY_H
