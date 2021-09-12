#ifndef PIECE_HPP
#define PIECE_HPP

#include "ability.hpp"
#include "entity.hpp"
#include "consumable.hpp"
#include "imagebutton.hpp"
#include <unordered_map>

enum class PieceType {pawn, rook, knight, bishop, queen, king, minion};

// 定义棋子类

class Piece: public Entity {

    Q_OBJECT
    Q_PROPERTY (QPointF pos READ pos WRITE setPos)

    QString capitalizeFirst(QString text) const;

protected:

    //void mousePressEvent(QGraphicsSceneMouseEvent *event);

    //void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    //void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    std::unordered_map<QString, int> stats_ = {
        {"health", 100},
        {"damage", 20},
        {"energy", 100},
        {"speed", 5},
        {"range", 3},
    };

    bool playerPiece_ = true;
    Ability spell_;
    int movesLeft_ = stat("speed");
    bool usedAttack_ = false;

    Piece();

public:



    const Ability& spell() const;

    void moved();
    void skipped();
    int movesLeft() const;

    bool inRange(Piece* piece);
    QString info() const;
    bool playerPiece() const;

    int stat(const QString& stat) const;
    void setStat(const QString& stat, int amount);

    void consume(Consumable *consumable);
    void useAttack(Piece *piece);
    void useSpell(Piece *piece);
    bool canUseAttack() const;
    bool canUseSpell() const;


    QTimer flashTimer_;


private slots:

    void flash();


signals:

    //void hoverEnter(Piece*);
    //void hoverLeave(Piece*);
    // clicked(Piece*);


};

class Pawn: public Piece {
public:
    Pawn();
};

class Rook: public Piece {
public:
    Rook();
};
class Knight: public Piece {
public:
    Knight();
};
class Bishop: public Piece {
public:
    Bishop();
};
class Queen: public Piece {
public:
    Queen();
};
class King: public Piece {
public:
    King();
};

class Minion: public Piece {
public:
    Minion();
};

Piece* buildPiece(PieceType pieceType);

#endif // PIECE_HPP
