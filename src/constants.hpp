#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <QPoint>

namespace Constants {
    const int boardWidth = 32;
    const int boardHeight = 32;
    const int squareSize = 100;
    const int totalWidth = boardWidth * squareSize;
    const int totalHeight = boardHeight * squareSize;
    const int buttonSize = squareSize / 4;
}

inline bool onBoard(const QPoint& position) {
    return position.x() >= 0 && position.x() < Constants::boardWidth
        && position.y() >= 0 && position.y() < Constants::boardHeight;
}

inline bool onBoardOffset(const QPoint& position) {
    return position.x() > 0 && position.x() <= Constants::boardWidth
        && position.y() > 0 && position.y() <= Constants::boardHeight;
}



#endif // CONSTANTS_HPP
