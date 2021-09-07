#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "entity.hpp"
#include <QtWidgets>





class Terrain: public Entity {

protected:
    int z_ = 0;
    bool occupiable_ = true;
    bool hidesOccupant_;
    bool showOccupiable_ = false;

public:

    bool occupiable() const {
        return occupiable_;
    }



};

class Rock: public Terrain {

public:
    Rock() {
        blocksVision_ = true;
        occupiable_ = false;
        image_ = QPixmap(":/res/img/rock_border.png");
    }
    //QPixmap

};

class Bush: public Terrain {

    bool occupiable_ = true;
    bool hidesOccupant_ = false;

};

class Grass: public Terrain {


    //QPixmap img = QPixmap(":/res/img/grass_border.png");
public:
    Grass() {
        occupiable_ = true;
        hidesOccupant_ = false;
        image_ = QPixmap(":/res/img/grass_border.jpg");
    }

};

#endif // TERRAIN_HPP
