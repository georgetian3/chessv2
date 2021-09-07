#ifndef RANGEMARKER_HPP
#define RANGEMARKER_HPP

#include "constants.hpp"
#include <QtWidgets>



enum class SideType {north, east, south, west};


class RangeMarker: public QGraphicsLineItem {
public:
    RangeMarker(QPoint position, SideType side, QGraphicsLineItem * parent = 0): QGraphicsLineItem(parent) {
        setPos(position * Constants::squareSize);
        QPen pen;
        pen.setColor(QColor(100, 100, 255));
        pen.setWidth(10);
        setPen(pen);
        switch (side) {
            case SideType::north:
                setLine(0, 0, Constants::squareSize, 0);
                break;
            case SideType::east:
                setLine(Constants::squareSize, 0, Constants::squareSize, Constants::squareSize);
                break;
            case SideType::south:
                setLine(0, Constants::squareSize, Constants::squareSize, Constants::squareSize);
                break;
            case SideType::west:
                setLine(0, 0, 0, Constants::squareSize);
                break;
        }
    }
};

#endif // RANGEMARKER_HPP
