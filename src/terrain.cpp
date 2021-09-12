#include "terrain.hpp"

Terrain::Terrain() {
    setZValue(0);
}


Rock::Rock() {
    setImage(":/res/img/rock_border.png");
    blocksVision_ = true;
    occupiable_ = false;
}



Grass::Grass() {
    setImage(":/res/img/grass_border.jpg");
    occupiable_ = true;
}
