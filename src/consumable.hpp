#ifndef CONSUMABLE_HPP
#define CONSUMABLE_HPP

#include "entity.hpp"
#include <QtWidgets>

class Consumable: public Entity {

protected:

    QString stat_;
    int amount_;

public:

    Consumable() {
        setZValue(1);
    }
    QString stat() const {
        return stat_;
    }
    int amount() const {
         return amount_;
    }
};

enum class ConsumableType {sword, firstAid, energyDrink, shoes, binoculars};

const std::vector<ConsumableType> ConsumableTypes = {ConsumableType::sword, ConsumableType::firstAid, ConsumableType::energyDrink, ConsumableType::shoes, ConsumableType::binoculars};

class Binoculars: public Consumable {
public:
    Binoculars() {
        setImage(":/res/img/binoculars.png");
        stat_ = "range";
        amount_ = 1;
    }
};

class FirstAid: public Consumable {

public:
    FirstAid() {
        setImage(":/res/img/firstaid.png");
        stat_ = "health";
        amount_ = 20;
    }
};

class EnergyDrink: public Consumable {

public:
    EnergyDrink() {
        setImage(":/res/img/drink.png");
        stat_ = "energy";
        amount_ = 50;
    }
};

class Shoes: public Consumable {

public:
    Shoes() {
        setImage(":/res/img/shoes.png");
        stat_ = "speed";
        amount_ = 1;
    }
};

class Sword: public Consumable {

public:
    Sword() {
        setImage(":/res/img/sword.png");
        stat_ = "damage";
        amount_ = 20;
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
