#ifndef __CHESSAI_HPP
#define __CHESSAI_HPP

#include "chessboard.hpp"
#include <iostream>
#include <string>
#include <map>
#include <utility>
#include <random>

class ChessAI {
private:
    std::string color;
    
    std::string convertMove(std::pair<std::pair<int,int>, std::pair<int,int>> move);
    std::string convertToLetter(int n);
public:
    ChessAI(std::string c) : color(c) {}
    std::string getNextMove(Chessboard& board);
};



#endif