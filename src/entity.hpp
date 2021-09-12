#ifndef ENTITY_H
#define ENTITY_H

#include "constants.hpp"
#include <QGraphicsPixmapItem>

class Entity: public QObject, public QGraphicsItem {

    Q_OBJECT

protected:

    QGraphicsPixmapItem image_ = QGraphicsPixmapItem(this);

    bool occupiable_ = true;
    bool blocksVision_ = false;

    QPoint coordinates_;
    QString name_;
    QString info_;

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override {}
    QRectF boundingRect() const override;

public:

    Entity();

    void setImage(const QString& imagePath = ":/res/img/placeholder.png");
    bool blocksVision() const;
    bool occupiable() const;

    QString info() const;

    QPoint coordinates() const;

    // setCoordinates会默认调用QGraphicsItem的setPos函数，
    // 如果通过其他方式更改本类的位置，比如平移动画，可以设callSetPos为false，
    // 避免再次调用setPos
    void setCoordinates(const QPoint& coordinates, bool callSetPos = true);

};


#endif // ENTITY_H
