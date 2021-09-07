#ifndef ENTITY_H
#define ENTITY_H

#include "constants.hpp"
#include <QtWidgets>

class Entity: public QObject, public QGraphicsItem {
    Q_OBJECT

protected:


    QPixmap image_ = QPixmap(":/res/img/placeholder.png");
    QPixmap mask_ = QPixmap(Constants::squareSize, Constants::squareSize);
    void makePixmap();
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    QPoint coordinates_;
    bool blocksVision_ = false;
    QString name_;
    QString description_;
    QString sound;
    QString info_;
    int z_;

public:

    Entity();


    bool blocksVision();
    QString name() const;
    QString info() const;
    QPoint coordinates() const;
    void setCoordinates(const QPoint& coordinates);


signals:

    void entityClicked(Entity*);


};




#endif // ENTITY_H
