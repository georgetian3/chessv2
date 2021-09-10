#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

//#include <QPoint>
#include <QRectF>

namespace Constants {
    const int boardWidth = 32;
    const int boardHeight = 32;
    const int squareSize = 100;
    const int totalWidth = boardWidth * squareSize;
    const int totalHeight = boardHeight * squareSize;
    const int buttonSize = squareSize / 2;
    const QRectF squareRect(0, 0, squareSize, squareSize);
    const QPoint target1(Constants::boardWidth / 2 - 1, 0);
    const QPoint target2(Constants::boardWidth / 2, 0);
}

inline bool onBoard(const QPoint& position) {
    return position.x() >= 0 && position.x() < Constants::boardWidth
        && position.y() >= 0 && position.y() < Constants::boardHeight;
}

inline bool onBoardOffset(const QPoint& position) {
    return position.x() > 0 && position.x() <= Constants::boardWidth
        && position.y() > 0 && position.y() <= Constants::boardHeight;
}

inline int dist(QPoint a, QPoint b) {
    return (a - b).manhattanLength();
}



#endif // CONSTANTS_HPP
