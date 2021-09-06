#ifndef PIECE_HPP
#define PIECE_HPP

#include "squareobject.hpp"

#include <QtWidgets>
#include <unordered_map>


enum class PieceType {pawn, rook, knight, bishop, queen, king, minion};


class Piece: public SquareObject {

protected:

    std::unordered_map<QString, int> stats_ = {
        {"health", 0},
        {"damage", 0},
        {"energy", 0},
        {"speed", 5},
        {"range", 3},
    };

    std::string ability_description;

    void setStat(const QString& stat, int amount) {
        auto it = stats_.find(stat);
        if (it != stats_.end()) {
            (*it).second += amount;
            if ((*it).second < 0) {
                (*it).second = 0;
            }
        }
    }

    //virtual void move() = 0;
    void attack(Piece& piece) {
        piece.setStat("health", -1 * stats_["damage"]);
    }
    //virtual void ability(Piece& piece) = 0;

    QString capitalizeFirst(QString text) const {
        text[0] = text[0].toUpper();
        return text;
    }


public:

    Piece() {
        info_ = "<center><b>Test</b><center><br>test";
    }

    QString info() const {
        QString info;
        info += "<b>"  + name_ + "</b><br>";
        for (const auto& [stat, value]: stats_) {
            info += capitalizeFirst(stat) + ": " + QString::number(value) + "<br>";
        }
        return info;
    }

    int getStat(const QString& stat) const {
        auto it = stats_.find(stat);
        if (it != stats_.end()) {
            return it->second;
        } else {
            return -1;
        }
    }

    const std::unordered_map<QString, int>& stats() const {
        return stats_;
    }

};

class PlayerPiece: public Piece {

};

class Pawn: public PlayerPiece {
public:
    Pawn() {
        img_ = QPixmap(":/res/img/pawn_w.png");
        name_ = "Pawn";
    }
};

class Rook: public PlayerPiece {
public:
    Rook() {
        img_ = QPixmap(":/res/img/rook_w.png");
        name_ = "Rook";
    }
};
class Knight: public PlayerPiece {
public:
    Knight() {
        img_ = QPixmap(":/res/img/knight_w.png");
        name_ = "Knight";
    }
};
class Bishop: public PlayerPiece {
public:
    Bishop() {
        img_ = QPixmap(":/res/img/bishop_w.png");
        name_ = "Bishop";
    }
};
class Queen: public Piece {
public:
    Queen() {
        img_ = QPixmap(":/res/img/queen_w.png");
        name_ = "Queen";
    }
};
class King: public Piece {
public:
    King() {
        img_ = QPixmap(":/res/img/king_w.png");
        name_ = "King";
    }

};

class Minion: public Piece {
public:
    Minion() {
        img_ = QPixmap(":/res/img/pawn_b.png");
        name_ = "Minion";
    }
};

#endif // PIECE_HPP
