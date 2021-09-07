#ifndef CONSUMABLE_HPP
#define CONSUMABLE_HPP

#include "entity.hpp"
#include <QtWidgets>

class Consumable: public Entity {
    std::string stat;
    int amount;
    int z_ = 1;
};


#endif // CONSUMABLE_HPP
