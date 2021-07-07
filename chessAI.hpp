#ifndef __CHESSAI_HPP
#define __CHESSAI_HPP

#include "chessboard.hpp"
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <ctime>

class ChessAI {
private:
    std::string color;
    
    int getValueOfPiece(Piece* piece);
public:
    ChessAI(std::string c) : color(c) {}
    std::pair<std::pair<int,int>, std::pair <int,int>> getNextMove(Chessboard& board);
};



#endif