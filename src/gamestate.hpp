#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include "square.hpp"
#include <QtWidgets>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace Constants {
    const int board_length = 64;
    const int board_width = 64;
}


class Terrain: public SquareObject {

protected:

    bool traversable;
    bool stackable;

};

class Rock: public Terrain {
public:
    Rock(QGraphicsItem *parent = nullptr) {
        img = QPixmap(":/res/img/rock.jpg");
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override {
        painter->drawPixmap(0, 0, 100, 100, img);
    }

};

class Bush: public Terrain {

};

class Grass: public Terrain {
public:
    Grass(QGraphicsItem *parent = nullptr) {
        img = QPixmap(":/res/img/grass_border.jpg");
    }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override {
        painter->drawPixmap(0, 0, 100, 100, img);
    }
};

class Consumable: public SquareObject {
    std::string stat;
    int amount;
};

class Piece: public SquareObject {

protected:

    std::unordered_map<std::string, int> stats = {
        {"health", 0},
        {"damage", 0},
        {"energy", 0},
        {"speed", 0},
        {"vision", 0},
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

    virtual void move() = 0;
    virtual void attack(Piece& piece) {
        piece.changeStat("health", -1 * stats["damage"]);
    }
    virtual void ability(Piece& piece) = 0;

};




class Position {

    const std::vector<int> adjacentMoves = {-1, 0, 1};

public:

    int x_;
    int y_;

    Position(int x, int y): x_(x), y_(y) {

    }

    std::vector<Position> getAdjacent() const {
        std::vector<Position> adjacents;
        for (int moveX: adjacentMoves) {
            for (int moveY: adjacentMoves) {
                if (moveX == 0 && moveY == 0) {
                    continue;
                }
                int newX = x_ + moveY;
                int newY = y_ + moveY;
                if (!(newX < 0 || newY < 0 || newX >= Constants::board_length || newY >= Constants::board_width)) {
                    adjacents.push_back(Position(newX, newY));
                }
            }
        }

    }
};




class GameState {
    bool turn;
    
    //Board board;
};


#endif
