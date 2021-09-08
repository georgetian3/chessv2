#ifndef IMAGEBUTTON_HPP
#define IMAGEBUTTON_HPP

#include "constants.hpp"
#include <QtWidgets>

enum class CornerType {nw, ne, sw, se};

class ImageButton: public QObject, public QGraphicsItem {
    Q_OBJECT
    QPixmap image_;
    bool enabled_ = true;
    QPixmap mask_ = QPixmap(Constants::buttonSize, Constants::buttonSize);
public:
    ImageButton(const QString& path, QGraphicsItem *parent = nullptr): QGraphicsItem(parent) {
        setZValue(3);
        mask_.fill(QColor(0, 0, 0, 100));
        image_ = QPixmap(path);
        image_ = image_.scaled(Constants::buttonSize, Constants::buttonSize,
                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override {
        painter->drawPixmap(0, 0, image_.size().width(), image_.size().height(), image_);
        if (!enabled_) {
            painter->drawPixmap(0, 0, image_.size().width(), image_.size().height(), mask_);
        }
    }

    void setCoordinates(QPoint coordinates, CornerType corner = CornerType::nw) {
        coordinates *= Constants::squareSize;
        if (corner == CornerType::ne || corner == CornerType::se) {
            coordinates.setX(coordinates.x() + Constants::squareSize - Constants::buttonSize);
        }
        if (corner == CornerType::sw || corner == CornerType::se) {
            coordinates.setY(coordinates.y() + Constants::squareSize - Constants::buttonSize);
        }
        setPos(coordinates);
    }

    QRectF boundingRect() const override {
        return QRectF(0, 0, Constants::squareSize, Constants::squareSize);
    }

public slots:

    void setEnabled(bool enabled) {
        enabled_ = enabled;
        update();
    }

    void mousePressEvent(QGraphicsSceneMouseEvent* event) override {
        if (enabled_) {
            emit clicked();
        }
        //QGraphicsItem::mousePressEvent(event);
    }
signals:
    void clicked();
};


#endif // IMAGEBUTTON_HPP
