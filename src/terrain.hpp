#ifndef TERRAIN_HPP
#define TERRAIN_HPP

#include "entity.hpp"

// 定义“地形”类及其子类，“草坪”和“岩石”

class Terrain: public Entity {

protected:

    Terrain();

};

class Rock: public Terrain {

public:
    Rock();
};


class Grass: public Terrain {

public:
    Grass();

};

#endif // TERRAIN_HPP
