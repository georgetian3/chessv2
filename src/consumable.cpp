#include "consumable.hpp"

Consumable::Consumable() {
    setZValue(1);
}
QString Consumable::stat() const {
    return stat_;
}
int Consumable::amount() const {
     return amount_;
}


Telescope::Telescope() {
    setImage(":/res/img/binoculars.png");
    stat_ = "range";
    amount_ = 1;
}


FirstAid::FirstAid() {
    setImage(":/res/img/firstaid.png");
    stat_ = "health";
    amount_ = 20;
}



Food::Food() {
    setImage(":/res/img/drink.png");
    stat_ = "energy";
    amount_ = 50;
}


Shoes::Shoes() {
    setImage(":/res/img/shoes.png");
    stat_ = "speed";
    amount_ = 1;
}

Sword::Sword() {
    setImage(":/res/img/sword.png");
    stat_ = "damage";
    amount_ = 20;
}

Consumable* buildConsumable(ConsumableType consumableType) {
    switch (consumableType) {
        case ConsumableType::sword:
            return new Sword();
        case ConsumableType::firstAid:
            return new FirstAid();
        case ConsumableType::food:
            return new Food();
        case ConsumableType::shoes:
            return new Shoes();
        case ConsumableType::telescope:
            return new Telescope();
        default:
            qDebug() << "buildConsumable unknown consumableType";
            return nullptr;
    }
}
