#ifndef __CHESSBOARD_HPP
#define __CHESSBOARD_HPP


#include <iostream>
#include <string>

struct Piece {
    Piece(std::string c, std::string t) {
        color = c;
        type = t;
    }
    std::string color;
    std::string type;
};

class Chessboard {
private:
    Piece* board[8][8];
    bool isWhiteInCheck;
    bool isBlackInCheck;
    bool isWhiteInCheckmate;
    bool isBlackInCheckmate;
    
    void add_piece(std::string color, std::string type, int xcord, int ycord);
public:
    Chessboard();
    void print_board();
};

#endif