#ifndef SQUAREOBJECT_HPP
#define SQUAREOBJECT_HPP

#include <QtWidgets>

class SquareObject {

protected:

    bool blocksVision_ = false;
    QString name_;
    QString description_;
    QString sound;
    QString info_;


    QPixmap img_ = QPixmap(":/res/img/placeholder.png");


public:


    SquareObject() {
        img_ = img_.scaledToHeight(100);

    }

    bool blocksVision() {
        return blocksVision_;
    }

    const QPixmap& img() const {
        return img_;
    }

    const QString name() const {
        return name_;
    }

    QString info() const {
        return name_ + '\n' + description_;
    }


};

#endif // SQUAREOBJECT_HPP
