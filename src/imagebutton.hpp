#ifndef IMAGEBUTTON_HPP
#define IMAGEBUTTON_HPP

#include "constants.hpp"
#include <QGraphicsItem>


// 显示图像的按钮

class ImageButton: public QObject, public QGraphicsItem {

    Q_OBJECT

    QGraphicsPixmapItem image_{QGraphicsPixmapItem(this)};

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override {}
    QRectF boundingRect() const override;

public:

    ImageButton(const QString& path, QGraphicsItem *parent = nullptr);

private slots:

    void mousePressEvent(QGraphicsSceneMouseEvent*) override;

signals:

    void clicked();

};


#endif // IMAGEBUTTON_HPP
