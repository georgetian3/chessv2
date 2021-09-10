#ifndef PIECE_HPP
#define PIECE_HPP

#include "ability.hpp"
#include "consumable.hpp"
#include "entity.hpp"
#include "imagebutton.hpp"
#include <QtWidgets>
#include <unordered_map>

enum class PieceType {pawn, rook, knight, bishop, queen, king, minion};

class Piece: public Entity {

    Q_OBJECT
    Q_PROPERTY (QPointF pos READ pos WRITE setPos)

    QString capitalizeFirst(QString text) const;

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

    QString spellDescription_;
    std::unordered_map<QString, int> stats_ = {
        {"health", 100},
        {"damage", 20},
        {"energy", 100},
        {"speed", 5},
        {"range", 3},
    };
    int movesLeft_ = getStat("speed");
    bool playerPiece_ = true;
    Ability spell_;

    bool usedSpell_ = false;
    bool usedAttack_ = false;



public:

    Piece();

    const Ability& spell() const;

    void moved();
    void skipped();
    int movesLeft() const;
    bool inRange(Piece* piece);
    QString info() const;
    bool playerPiece() const;
    int getStat(const QString& stat) const;
    void setStat(const QString& stat, int amount);
    void consume(Consumable *consumable);
    const std::unordered_map<QString, int>& stats() const;
    void useAttack(Piece *piece);
    void useSpell(Piece *piece);

    bool canUseSpell() const;
    bool canUseAttack() const;
    QTimer flashTimer;


private slots:

    void flash();


signals:

    void hoverEnter(Piece*);
    void hoverLeave(Piece*);
    void clicked(Piece*);


};















class Pawn: public Piece {
public:
    Pawn() {
        setImage(":/res/img/pawn_w.png");
        name_ = "Pawn";
        playerPiece_ = true;
        stats_ = {
            {"health", 10},
            {"damage", 5},
            {"energy", 100},
            {"speed", 5},
            {"range", 5},
        };
        spell_.setAmount(-1);
        spell_.setStat("range");
        spell_.setTarget(TargetType::enemy);
        spell_.setCost(50);
        movesLeft_ = getStat("speed");
    }
};

class Rook: public Piece {
public:
    Rook() {
        setImage(":/res/img/rook_w.png");
        name_ = "Rook";
        playerPiece_ = true;
        stats_ = {
            {"health", 50},
            {"damage", 20},
            {"energy", 100},
            {"speed", 2},
            {"range", 3},
        };
        spell_.setAmount(-5);
        spell_.setStat("damage");
        spell_.setTarget(TargetType::enemy);
        spell_.setCost(50);
        movesLeft_ = getStat("speed");
    }
};
class Knight: public Piece {
public:
    Knight() {
        setImage(":/res/img/knight_w.png");
        name_ = "Knight";
        playerPiece_ = true;
        stats_ = {
            {"health", 20},
            {"damage", 5},
            {"energy", 100},
            {"speed", 5},
            {"range", 3},
        };
        spell_.setAmount(-1);
        spell_.setStat("speed");
        spell_.setTarget(TargetType::enemy);
        spell_.setCost(50);
        movesLeft_ = getStat("speed");
    }
};
class Bishop: public Piece {
public:
    Bishop() {
        setImage(":/res/img/bishop_w.png");
        name_ = "Bishop";
        playerPiece_ = true;
        stats_ = {
            {"health", 100},
            {"damage", 5},
            {"energy", 100},
            {"speed", 3},
            {"range", 3},
        };
        spell_.setAmount(10);
        spell_.setStat("health");
        spell_.setTarget(TargetType::ally);
        spell_.setCost(50);
        movesLeft_ = getStat("speed");
    }
};
class Queen: public Piece {
public:
    Queen() {
        setImage(":/res/img/queen_w.png");
        name_ = "Queen";
        playerPiece_ = true;
        stats_ = {
            {"health", 10},
            {"damage", 100},
            {"energy", 100},
            {"speed", 3},
            {"range", 5},
        };
        spell_.setAmount(1);
        spell_.setStat("range");
        spell_.setTarget(TargetType::enemy);
        spell_.setCost(50);
        movesLeft_ = getStat("speed");
    }
};
class King: public Piece {
public:
    King() {
        setImage(":/res/img/king_w.png");
        name_ = "King";
        playerPiece_ = true;
        stats_ = {
            {"health", 5},
            {"damage", 0},
            {"energy", 0},
            {"speed", 1},
            {"range", 1},
        };
        spell_.setTarget(TargetType::none);
        movesLeft_ = getStat("speed");
    }

};

class Minion: public Piece {
public:
    Minion() {
        setImage(":/res/img/pawn_b.png");
        name_ = "Minion";
        playerPiece_ = false;
        stats_ = {
            {"health", 20},
            {"damage", 5},
            {"energy", 100},
            {"speed", 10},
            {"range", 5},
        };
        spell_.setTarget(TargetType::none);
        movesLeft_ = getStat("speed");
    }
};

inline Piece* buildPiece(PieceType pieceType) {
    switch (pieceType) {
        case PieceType::pawn:
            return new Pawn();
        case PieceType::rook:
            return new Rook();
        case PieceType::knight:
            return new Knight();
        case PieceType::bishop:
            return new Bishop();
        case PieceType::queen:
            return new Queen();
        case PieceType::king:
            return new King();
        case PieceType::minion:
            return new Minion();
        default:
            qDebug() << "buildPiece unknown piecetype";
            return nullptr;
    }
}

#endif // PIECE_HPP
