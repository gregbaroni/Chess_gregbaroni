#include "chessAI.hpp"

// Function that generates the next move for the ai
// Uses the minMax function to iterate through a tree of possible moves
// and returns the move that results in the most points
std::pair<std::pair<int,int>, std::pair <int,int>>  ChessAI::getNextMove(Chessboard& board) {
    int currentValue = getValueOfBoard(board);
    return minMax(board, 0, currentValue).first;
}


// Function that determines the best move for the ai
// Takes as input the chessboard, depth, and current value of the board
// When it's calculating an ai response it maximizes the value of the board
// and when it's calcuting the player's response it minimizes the value of the board
// Returns a pair of (move, value)
std::pair<std::pair<std::pair<int,int>, std::pair <int,int>>, int> ChessAI::minMax(Chessboard& board, int depth, int currentValue) {
    bool aiTurn = false;
    if(depth % 2 == 0) {
        aiTurn = true;
    }

    std::string playerColor;
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> validMoves;
    if(aiTurn) {
        if(color == "white") {
            validMoves = board.getWhiteValidMoves();
            playerColor = "black";
        }
        else {
            validMoves = board.getBlackValidMoves();
            playerColor = "white";
        }
    }
    else {
        if(color == "white") {
            validMoves = board.getBlackValidMoves();
            playerColor = "black";
        }
        else {
            validMoves = board.getWhiteValidMoves();
            playerColor = "white";
        }        
    }

    Piece* p;
    std::pair<std::pair<int,int>, std::pair<int,int>> bestMove;
    std::pair<std::pair<std::pair<int,int>, std::pair <int,int>>, int> minMaxResult;
    int value;

    if(aiTurn) {
        int maxValue = 0;
        for(std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int>::iterator it = validMoves.begin(); it != validMoves.end(); it++) {
            Chessboard tempBoard = board;
            tempBoard.move(color, it->first.first, it->first.second);
            value = getValueOfBoard(tempBoard);

            if(depth + 1 < 2 && value >= currentValue) {
                minMaxResult = minMax(tempBoard, depth + 1, currentValue);
                value = minMaxResult.second;
            }

            if(it == validMoves.begin()) {
                bestMove = it->first;
                maxValue = value;
                currentValue = value;
            }
            else {
                if(value > maxValue) {
                    maxValue = value;
                    currentValue = value;
                    bestMove = it->first;
                }
            }
        }
        return std::make_pair(bestMove, maxValue);       
    }
    else {
        int minValue = 0;
        for(std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int>::iterator it = validMoves.begin(); it != validMoves.end(); it++) {
            Chessboard tempBoard = board;
            tempBoard.move(playerColor, it->first.first, it->first.second);
            value = getValueOfBoard(tempBoard);

            if(depth + 1 < 2 and value <= currentValue) {
                minMaxResult = minMax(tempBoard, depth + 1, currentValue);
                value = minMaxResult.second;
            }

            if(it == validMoves.begin()) {
                bestMove = it->first;
                minValue = value;
                currentValue = value;
            }
            else {
                if(value < minValue) {
                    minValue = value;
                    currentValue = value;
                    bestMove = it->first;
                }
            }
        }
        return std::make_pair(bestMove, minValue);     
    }

}


// Returns the current value of the board
int ChessAI::getValueOfBoard(Chessboard& board) {
    int sum = 0;
    Piece* p;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            p = board.getPieceAt(i,j);
            if(p != nullptr) {
                if(p->color == color) {
                    sum += getValueOfPiece(p);
                }
                else {
                    sum -= getValueOfPiece(p);
                }
            }
        }
    }
    return sum;
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