#ifndef SQUARE_HPP
#define SQUARE_HPP

#include <QtWidgets>

class SquareObject: public QGraphicsItem {

protected:
    QPixmap img;
    std::string name;
    std::string sound;
    int x;
    int y;

public:

    QRectF boundingRect() const override {
        return QRectF(0, 0, 100, 100);
    }

};

class Square: public QGraphicsItem {

public:
    Square(QGraphicsItem *parent = nullptr): QGraphicsItem(parent) {
        qDebug() << "Square ctor";


    }
    bool occupiable;
    int playerVision; // 0: never warded, 1: previously warded, 2: currently warded
    int enemyVision;
    int x;
    int y;
    std::vector<SquareObject> objects;
};

#endif // SQUARE_HPP
