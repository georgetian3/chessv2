#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <QRectF>

namespace Constants {
    const int boardWidth = 32; // 棋盘的宽度（单位：方格）
    const int boardHeight = 32; // 棋盘的高度（单位：方格）
    const int squareSize = 100; // 方格的宽度和高度（单位：像素）
    const int totalWidth = boardWidth * squareSize; // 棋盘的宽度（单位：像素）
    const int totalHeight = boardHeight * squareSize; // 棋盘的高度（单位：像素）
    const int buttonSize = squareSize / 2; // 按钮的宽度和高度（单位：像素）
    const QRectF squareRect(0, 0, squareSize, squareSize); // 方格的边界
    const QPoint target1(Constants::boardWidth / 2 - 1, 0); // 目标方格一的坐标位置
    const QPoint target2(Constants::boardWidth / 2, 0); // 目标方格二的坐标位置
}

// 判定坐标是否在棋盘上
inline bool onBoard(const QPoint& position) {
    return position.x() >= 0 && position.x() < Constants::boardWidth
        && position.y() >= 0 && position.y() < Constants::boardHeight;
}

inline bool onBoardOffset(const QPoint& position) {
    return position.x() > 0 && position.x() <= Constants::boardWidth
        && position.y() > 0 && position.y() <= Constants::boardHeight;
}

// 计算两点之间的曼哈顿距离
inline int dist(QPoint a, QPoint b) {
    return (a - b).manhattanLength();
}



#endif // CONSTANTS_HPP
