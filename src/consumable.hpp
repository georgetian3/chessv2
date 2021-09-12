#ifndef CONSUMABLE_HPP
#define CONSUMABLE_HPP

#include "entity.hpp"
#include <QtWidgets>

// 实现耗材类

class Consumable: public Entity {

protected:

    QString stat_;
    int amount_;
    Consumable();

public:

    QString stat() const;
    int amount() const;

};

enum class ConsumableType {sword, firstAid, food, shoes, telescope};

const std::vector<ConsumableType> ConsumableTypes = {ConsumableType::sword, ConsumableType::firstAid, ConsumableType::food, ConsumableType::shoes, ConsumableType::telescope};

class Telescope: public Consumable {
public:
    Telescope();
};

class FirstAid: public Consumable {
public:
    FirstAid();
};

class Food: public Consumable {
public:
    Food();
};

class Shoes: public Consumable {
public:
    Shoes();
};

class Sword: public Consumable {
public:
    Sword();
};

Consumable* buildConsumable(ConsumableType consumableType);

#endif // CONSUMABLE_HPP
