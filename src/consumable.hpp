#ifndef CONSUMABLE_HPP
#define CONSUMABLE_HPP

#include "squareobject.hpp"
#include <QtWidgets>

class Consumable: public SquareObject {
    std::string stat;
    int amount;
};


#endif // CONSUMABLE_HPP
