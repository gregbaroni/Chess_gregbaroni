#ifndef __CHESSBOARD_HPP
#define __CHESSBOARD_HPP


#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <limits>


// Struct to represent the pieces on the chessboard
struct Piece {
    Piece(std::string c, std::string t) {
        color = c;
        type = t;
        hasMoved = false;
        std::map<std::pair <int,int>, int> v;
        validMoves = v;
    }
    Piece(std::string c, std::string t, std::map<std::pair <int,int>, int> v) {
        color = c;
        type = t;
        hasMoved = false;
        validMoves = v;
    }
    std::string color;
    std::string type;
    // needed for castling
    bool hasMoved;
    // validMoves stores the spaces that the piece can move to
    std::map<std::pair <int,int>, int> validMoves;
};

// Class to represent the chessboard
class Chessboard {
private:
    Piece* board[8][8];
    /* whiteValidCaptures and blackValidCaptures store the spaces that the white pieces
     and black pieces can move to and capture pieces */
    std::map<std::pair <int,int>, int> whiteValidCaptures;
    std::map<std::pair <int,int>, int> blackValidCaptures;
    // whiteKingPos and blackKingPos store the positions of the kings
    std::pair<int,int> whiteKingPos;
    std::pair<int,int> blackKingPos;
    bool isWhiteInCheck;
    bool isBlackInCheck;
    bool isWhiteInCheckmate;
    bool isBlackInCheckmate;
    bool isStalemate;
    
    void addPiece(std::string color, std::string type, int xcord, int ycord);
    void validCapture(Piece* p, int x, int y);
    bool validPromotion(std::string promotion);
    void deleteBoard();
    int convertToNumber(char c);
public:
    Chessboard();
    ~Chessboard();
    Chessboard(const Chessboard& source);
    Chessboard& operator=(const Chessboard& source);
    void printBoard();
    bool validSpace(std::string space, int s);
    bool move(std::string player, std::string startSpace, std::string endSpace);
    void calculateBoardState(std::string player);
    void calculateValidMoves();
    void calculateKingStates(std::string player);
    const bool getIsWhiteInCheck();
    const bool getIsBlackInCheck();
    const bool getIsWhiteInCheckmate();
    const bool getIsBlackInCheckmate();
    const bool getIsStalemate();
};

#endif