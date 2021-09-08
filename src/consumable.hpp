#ifndef CONSUMABLE_HPP
#define CONSUMABLE_HPP

#include "entity.hpp"
#include <QtWidgets>

class Consumable: public Entity {
    std::string stat;
    int amount;
    int z_ = 1;
public:
    Consumable() {
        setZValue(1);
    }
};

enum class ConsumableType {sword, firstAid, energyDrink, shoes, binoculars};

const std::vector<ConsumableType> ConsumableTypes = {ConsumableType::sword, ConsumableType::firstAid, ConsumableType::energyDrink, ConsumableType::shoes, ConsumableType::binoculars};

class Binoculars: public Consumable {
public:
    Binoculars() {
        setImage(":/res/img/binoculars.png");
    }
};

class FirstAid: public Consumable {
    public:
    FirstAid() {
        setImage(":/res/img/firstaid.png");
    }
};

class EnergyDrink: public Consumable {
    public:
    EnergyDrink() {
        setImage(":/res/img/drink.png");
    }
};

class Shoes: public Consumable {
    public:
    Shoes() {
        setImage(":/res/img/shoes.png");
    }
};

class Sword: public Consumable {
    public:
    Sword() {
        setImage(":/res/img/sword.png");
    }
};

inline Consumable* buildConsumable(ConsumableType consumableType) {
    switch (consumableType) {
        case ConsumableType::sword:
            return new Sword();
        case ConsumableType::firstAid:
            return new FirstAid();
        case ConsumableType::energyDrink:
            return new EnergyDrink();
        case ConsumableType::shoes:
            return new Shoes();
        case ConsumableType::binoculars:
            return new Binoculars();
        default:
            qDebug() << "buildConsumable unknown consumableType";
            return nullptr;
    }
}

#endif // CONSUMABLE_HPP
