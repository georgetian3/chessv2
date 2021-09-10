#ifndef IMAGEBUTTON_HPP
#define IMAGEBUTTON_HPP

#include "constants.hpp"
#include <QtWidgets>

class ImageButton: public QObject, public QGraphicsItem {
    Q_OBJECT
    bool enabled_ = true;
    QGraphicsPixmapItem image_ = QGraphicsPixmapItem(this);
    QGraphicsPixmapItem mask_ = QGraphicsPixmapItem(this);
public:
    ImageButton(const QString& path, QGraphicsItem *parent = nullptr): QGraphicsItem(parent) {
        setZValue(3);

        QPixmap pix(Constants::buttonSize, Constants::buttonSize);

        pix.load(path);
        pix = pix.scaled(Constants::buttonSize, Constants::buttonSize);
        image_.setPixmap(pix);

        pix.fill(QColor(0, 0, 0, 200));
        mask_.setPixmap(pix);
        mask_.hide();

    }

    void paint(QPainter*, const QStyleOptionGraphicsItem*, QWidget*) override {
        //QGraphicsItem::paint(painter, item, widget);
    }

    QRectF boundingRect() const override {
        return QRectF(0, 0, Constants::buttonSize, Constants::buttonSize);
    }

public slots:

    void setEnabled(bool enabled) {
        //mask_.setVisible(!enabled);
        image_.setVisible(enabled);
    }

    void mousePressEvent(QGraphicsSceneMouseEvent*) override {
        if (enabled_) {
            emit clicked();
        }
        //QGraphicsItem::mousePressEvent(event);
    }
signals:
    void clicked();
};


#endif // IMAGEBUTTON_HPP
