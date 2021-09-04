#ifndef BOARD_HPP
#define BOARD_HPP

#include "gamestate.hpp"
#include <QtWidgets>

#include <set>
#include <string>
#include <vector>

class Board: public QGraphicsItemGroup {

public:

    Board(QGraphicsItemGroup *parent = nullptr): QGraphicsItemGroup(parent) {
        qDebug() << "Board ctor";



        for (int i = 0; i < 64; i++ ) {
            for (int j = 0; j < 64; j++) {
                QGraphicsItem *item;
                if (i % 2) {
                    item = new Grass();
                } else {
                    item = new Rock();
                }
                item->setPos(i * item->boundingRect().width(), j * item->boundingRect().height());
                addToGroup(item);
            }
        }


    }



    std::vector<std::vector<Square>> squares;
    std::set<Position> possibleMoves(const Position& start, const int speed) {
        std::vector<Position> adjacents = start.getAdjacent();
        return std::set<Position>();
    }


};

#endif // BOARD_HPP
