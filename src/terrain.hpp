#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "squareobject.hpp"
#include <QtWidgets>





class Terrain: public SquareObject {

protected:

    bool occupiable_;
    bool hidesOccupant;

public:

    bool occupiable() const {
        return occupiable_;
    }



};

class Rock: public Terrain {

    bool occupiable = false;

public:
    Rock() {
        pix = QPixmap(":/res/img/rock_border.png").scaledToHeight(100);
    }

};

class Bush: public Terrain {

    bool occupiable = true;
    bool hidesOccupant = false;

};

class Grass: public Terrain {

    bool occupiable = true;
    bool hidesOccupant = false;

public:
    Grass() {
        pix = QPixmap(":/res/img/grass_border.jpg").scaledToHeight(100);
    }


};

#endif // TERRAIN_HPP
