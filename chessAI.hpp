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
    int pawnValues[8][8];
    int knightValues[8][8];
    int bishopValues[8][8];
    int rookValues[8][8];
    int queenValues[8][8];
    int kingValues[8][8];
    
    int getValueOfPiece(Piece* piece, int x, int y);
    std::pair<std::pair<std::pair<int,int>, std::pair <int,int>>, int> minMax(Chessboard& board, int depth, int currentValue);
public:
    ChessAI(std::string c);
    std::pair<std::pair<int,int>, std::pair <int,int>> getNextMove(Chessboard& board);
    int getValueOfBoard(Chessboard& board);
};



#endif