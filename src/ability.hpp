#ifndef ABILITY_HPP
#define ABILITY_HPP

#include <QString>

class Piece;

enum class TargetType {none, ally, enemy, all};

// 定义“技能”类

class Ability {

    TargetType target_;
    QString stat_;
    int cost_;
    int amount_;

public:

    void setTarget(TargetType target);
    void setCost(int cost);
    void setStat(QString stat);
    void setAmount(int amount);
    TargetType target() const;
    int cost() const;
    void perform(Piece *piece);

};


#endif // ABILITY_HPP
