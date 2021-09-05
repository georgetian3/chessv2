#ifndef SQUAREOBJECT_HPP
#define SQUAREOBJECT_HPP

#include <QtWidgets>

class SquareObject {

protected:

    std::string name;
    std::string sound;
    int x;
    int y;

public:

    QPixmap pix = QPixmap(":/res/img/placeholder.png");

    SquareObject() {
        pix = pix.scaledToHeight(100);

    }


};

#endif // SQUAREOBJECT_HPP
