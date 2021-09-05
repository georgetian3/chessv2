#ifndef PIECE_HPP
#define PIECE_HPP

#include "squareobject.hpp"

#include <QtWidgets>
#include <unordered_map>



class Piece: public SquareObject {

public:

    std::unordered_map<std::string, int> stats = {
        {"health", 0},
        {"damage", 0},
        {"energy", 0},
        {"speed", 0},
        {"vision", 5},
    };

    std::string name;
    std::string ability_description;

    void changeStat(const std::string stat, int amount) {
        auto it = stats.find(stat);
        if (it != stats.end()) {
            (*it).second += amount;
            if ((*it).second < 0) {
                (*it).second = 0;
            }
        }
    }

    //virtual void move() = 0;
    virtual void attack(Piece& piece) {
        piece.changeStat("health", -1 * stats["damage"]);
    }
    //virtual void ability(Piece& piece) = 0;

public:

    Piece() {
        ;
    }


};

class PlayerPiece: public Piece {

public:
    PlayerPiece() {
        ;
    }


};

class Pawn: public Piece {
public:
    Pawn() {
        pix = QPixmap(":/res/img/pawn_w.png").scaledToHeight(100, Qt::SmoothTransformation);
    }
};

class Rook: public Piece {
public:
    Rook() {
        pix = QPixmap(":/res/img/rook_w.png").scaledToHeight(100, Qt::SmoothTransformation);
    }
};
class Knight: public Piece {
public:
    Knight() {
        pix = QPixmap(":/res/img/knight_w.png").scaledToHeight(100, Qt::SmoothTransformation);
    }
};
class Bishop: public Piece {
public:
    Bishop() {
        pix = QPixmap(":/res/img/bishop_w.png").scaledToHeight(100, Qt::SmoothTransformation);
    }
};
class Queen: public Piece {
public:
    Queen() {
        pix = QPixmap(":/res/img/queen_w.png").scaledToHeight(100, Qt::SmoothTransformation);
    }
};
class King: public Piece {
public:
    King() {
        pix = QPixmap(":/res/img/king_w.png").scaledToHeight(100, Qt::SmoothTransformation);
    }
};


#endif // PIECE_HPP
