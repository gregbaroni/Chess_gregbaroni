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
        justDoubleMoved = false;

    }
    std::string color;
    std::string type;
    // Needed for castling
    bool hasMoved;
    // Needed for en passant
    bool justDoubleMoved;
};

// Class to represent the chessboard
class Chessboard {
private:
    Piece* board[8][8];
    /* whitePossibleMoves and blackPossiblemoves store the spaces that the white pieces
     and black pieces can move to */
    /* whiteValidMoves and blackValidMoves store the possible moves which do not put the
     player's king in check */
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> whitePossibleMoves;
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> blackPossibleMoves;
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> whiteValidMoves;
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> blackValidMoves;
    // whiteKingPos and blackKingPos store the positions of the kings
    std::pair<int,int> whiteKingPos;
    std::pair<int,int> blackKingPos;
    bool isWhiteInCheck;
    bool isBlackInCheck;
    bool isWhiteInCheckmate;
    bool isBlackInCheckmate;
    bool isStalemate;
    
    void addPiece(std::string color, std::string type, int xcord, int ycord);
    void possibleMove(Piece* p, std::pair<int,int> startCoords, int x, int y);
    bool canBlackCapture(std::pair<int,int> endCoords);
    bool canWhiteCapture(std::pair<int,int> endCoords);
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
    void calculatePossibleMoves();
    void calculateKingStates(std::string player);
    const bool getIsWhiteInCheck();
    const bool getIsBlackInCheck();
    const bool getIsWhiteInCheckmate();
    const bool getIsBlackInCheckmate();
    const bool getIsStalemate();
    const std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> getWhiteValidMoves();
    const std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> getBlackValidMoves();
};

#endif