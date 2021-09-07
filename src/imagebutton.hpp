#ifndef IMAGEBUTTON_HPP
#define IMAGEBUTTON_HPP

#include "constants.hpp"
#include <QtWidgets>

enum class CornerType {nw, ne, sw, se};

class ImageButton: public QObject, public QGraphicsItem {
    Q_OBJECT
    QPixmap image_;
public:
    ImageButton(const QString& path, QGraphicsItem *parent = nullptr): QGraphicsItem(parent) {
        setZValue(3);
        image_ = QPixmap(path);
        image_ = image_.scaled(Constants::buttonSize, Constants::buttonSize,
                               Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    }
    QRectF boundingRect() const override {
        return QRect(0, 0, image_.size().width(), image_.size().height());
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem*, QWidget*) override {
        painter->drawPixmap(0, 0, image_.size().width(), image_.size().height(), image_);
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

public slots:
    void mousePressEvent(QGraphicsSceneMouseEvent*) override {
        emit clicked();
    }
signals:
    void clicked();
};


#endif // IMAGEBUTTON_HPP
