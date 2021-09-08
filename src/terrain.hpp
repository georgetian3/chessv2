#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "entity.hpp"
#include <QtWidgets>




enum class TerrainType {grass, rock, bush};

class Terrain: public Entity {

protected:
    int z_ = 0;
    bool occupiable_ = true;
    bool hidesOccupant_;
    bool showOccupiable_ = false;

public:

    Terrain() {
        setZValue(0);
    }

    bool occupiable() const {
        return occupiable_;
    }



};

class Rock: public Terrain {

public:
    Rock() {
        setImage(":/res/img/rock_border.png");
        blocksVision_ = true;
        occupiable_ = false;
    }

};

class Bush: public Terrain {

    bool occupiable_ = true;
    bool hidesOccupant_ = false;

};

class Grass: public Terrain {

public:
    Grass() {
        setImage(":/res/img/grass_border.jpg");
        occupiable_ = true;
        hidesOccupant_ = false;
    }

};

#endif // TERRAIN_HPP
