#include "chessAI.hpp"

// Function that generates the next move for the ai
// Currently chooses the move that gives it the most points
// If two moves give the same amount of points, it chooses between them at random
std::pair<std::pair<int,int>, std::pair <int,int>>  ChessAI::getNextMove(Chessboard& board) {
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> validMoves;
    if(color == "white") {
        validMoves = board.getWhiteValidMoves();
    }
    else {
        validMoves = board.getBlackValidMoves();
    }

    // Initialize random number generator
    std::srand(std::time(0));
    int n;

    Piece* p;
    std::pair<std::pair<int,int>, std::pair<int,int>> bestMove;
    int value;
    int maxValue = 0;
    for(std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int>::iterator it = validMoves.begin(); it != validMoves.end(); it++) {
        p = board.getPieceAt(it->first.second.first, it->first.second.second);
        if(it == validMoves.begin()) {
            bestMove = it->first;
            maxValue = getValueOfPiece(p);
        }
        else {
            value = getValueOfPiece(p);
            if(value > maxValue) {
                maxValue = value;
                bestMove = it->first;
            }
            if(value == maxValue) {
                n = std::rand()%4;
                if(n > 2) {
                    bestMove = it->first;
                }
            } 
        }
    }

    return bestMove;
}

// Returns the point value of a piece
int ChessAI::getValueOfPiece(Piece* piece) {
    if(piece == nullptr) {
        return 0;
    }
    else if(piece->type == "pawn") {
        return 1;
    }
    else if(piece->type == "knight") {
        return 3;
    }
    else if(piece->type == "bishop") {
        return 3;
    }
    else if(piece->type == "rook") {
        return 5;
    }
    else if(piece->type == "queen") {
        return 9;
    }
    else if(piece->type == "king") {
        return 100;
    }
    else {
        return 0;
    }
 }