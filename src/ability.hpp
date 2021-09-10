#ifndef ABILITY_HPP
#define ABILITY_HPP

#include <QString>

class Piece;

enum class TargetType {none, ally, enemy, all};

class Ability {
protected:
    TargetType target_;
    int cost_;
    QString stat_;
    int amount_;
public:
    void setTarget(TargetType target) {
        target_ = target;
    }
    void setCost(int cost) {
        cost_ = cost;
    }
    void setStat(QString stat) {
        stat_ = stat;
    }
    void setAmount(int amount) {
        amount_ = amount;
    }
    TargetType target() const {
        return target_;
    }
    int cost() const {
        return cost_;
    }
    void perform(Piece *piece);
};


#endif // ABILITY_HPP
