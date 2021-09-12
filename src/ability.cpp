#include "ability.hpp"
#include "piece.hpp"

void Ability::setTarget(TargetType target) {
    target_ = target;
}
void Ability::setCost(int cost) {
    cost_ = cost;
}
void Ability::setStat(QString stat) {
    stat_ = stat;
}
void Ability::setAmount(int amount) {
    amount_ = amount;
}
TargetType Ability::target() const {
    return target_;
}
int Ability::cost() const {
    return cost_;
}
void Ability::perform(Piece *piece) {
    piece->setStat(stat_, amount_);
}
