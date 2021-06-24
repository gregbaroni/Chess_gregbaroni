#ifndef __CHESSBOARD_HPP
#define __CHESSBOARD_HPP


#include <iostream>
#include <string>
#include <vector>
#include <utility>

// Struct to represent the pieces on the chessboard
struct Piece {
    Piece(std::string c, std::string t) {
        color = c;
        type = t;
        std::vector<std::pair <int,int>> v;
        validMoves = v;
    }
    std::string color;
    std::string type;
    std::vector<std::pair <int,int>> validMoves;
    // validMoves stores the spaces that the piece can move to
};

// Class to represent the chessboard
class Chessboard {
private:
    Piece* board[8][8];
    std::vector<std::pair <int,int>> whiteValidMoves;
    std::vector<std::pair <int,int>> blackValidMoves;
    /* whiteValidMoves and blackValidMoves store the spaces that the white pieces
     and black pieces can move to */
    std::pair<int,int> whiteKingPos;
    std::pair<int,int> blackKingPos;
    /* whiteKingPos and blackKingPos store the positions of the kings */
    bool isWhiteInCheck;
    bool isBlackInCheck;
    bool isWhiteInCheckmate;
    bool isBlackInCheckmate;
    bool isStalemate;
    
    void addPiece(std::string color, std::string type, int xcord, int ycord);
    int convertToNumber(char c);
public:
    Chessboard();
    void printBoard();
    bool validSpace(std::string space);
    bool move(std::string player, std::string startSpace, std::string endSpace);
    void calculateValidMoves();
    bool getIsWhiteInCheckmate();
    bool getIsBlackInCheckmate();
    bool getIsStalemate();
};

#endif