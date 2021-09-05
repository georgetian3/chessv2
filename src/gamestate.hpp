#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <QtWidgets>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

namespace Constants {
    const int boardLength = 32;
    const int boardWidth = 32;
    const int squareSize = 100;
    const int totalLength = boardLength * squareSize;
    const int totalWidth = boardWidth * squareSize;
}






class GameState {
    bool turn;
    
    //Board board;
};


#endif
