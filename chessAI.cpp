#include "chessAI.hpp"

// Constructor for the AI, which takes the color of the pieces that the AI is controlling as input
ChessAI::ChessAI(std::string c) {
    color = c;

    // Stores the value of the pieces depending on their position on the board
    int pawn[8][8] = {
        {0,  0,  0,  0,  0,  0,  0,  0},
        {10,  10,  10,  10,  10,  10,  10,  10},
        {2,  2,  4,  6,  6,  4,  2,  2},
        {1,  1,  2,  5,  5,  2,  1,  1},
        {0,  0,  0,  4,  4,  0,  0,  0},
        {1, -1, -2,  0,  0, -2, -1,  1},
        {1,  2, 2,  -4, -4,  2,  2,  1},
        {0,  0,  0,  0,  0,  0,  0,  0}
    };

    int knight[8][8] = {
        {-10, -8, -6, -6, -6, -6, -8, -10},
        {-8, -4,  0,  0,  0,  0, -4, -8},
        {-6,  0,  2,  3,  3,  2,  0, -6},
        {-6,  1,  3,  4,  4,  3,  1, -6},
        {-6,  0,  3,  4,  4,  3,  0, -6},
        {-6,  1,  2,  3,  3,  2,  1, -6},
        {-8, -4,  0,  1,  1,  0, -4, -8},
        {-10, -8, -6, -6, -6, -6, -8, -10}
    };

    int bishop[8][8] = {
        { -4, -2, -2, -2, -2, -2, -2, -4},
        { -2,  0,  0,  0,  0,  0,  0, -2},
        { -2,  0,  1,  2,  2,  1,  0, -2},
        { -2,  1,  1,  2,  2,  1,  1, -2},
        { -2,  0,  2,  2,  2,  2,  0, -2},
        { -2,  2,  2,  2,  2,  2,  2, -2},
        { -2,  1,  0,  0,  0,  0,  1, -2},
        { -4, -2, -2, -2, -2, -2, -2, -4}
    };

    int rook[8][8] = {
        {  0,  0,  0,  0,  0,  0,  0,  0},
        {  1,  2,  2,  2,  2,  2,  2,  1},
        { -1,  0,  0,  0,  0,  0,  0, -1},
        { -1,  0,  0,  0,  0,  0,  0, -1},
        { -1,  0,  0,  0,  0,  0,  0, -1},
        { -1,  0,  0,  0,  0,  0,  0, -1},
        { -1,  0,  0,  0,  0,  0,  0, -1},
        {  0,   0, 0,  1,  1,  0,  0,  0}
    };

    int queen[8][8] = {
        { -4, -2, -2, -1, -1, -2, -2, -4},
        { -2,  0,  0,  0,  0,  0,  0, -2},
        { -2,  0,  1,  1,  1,  1,  0, -2},
        { -1,  0,  1,  1,  1,  1,  0, -1},
        {  0,  0,  1,  1,  1,  1,  0, -1},
        { -2,  1,  1,  1,  1,  1,  0, -2},
        { -2,  0,  1,  0,  0,  0,  0, -2},
        { -4, -2, -2, -1, -1, -2, -2, -4}
    };

    int king[8][8] = {
        { -6, -8, -8, -10, -10, -8, -8, -6},
        { -6, -8, -8, -10, -10, -8, -8, -6},
        { -6, -8, -8, -10, -10, -8, -8, -6},
        { -6, -8, -8, -10, -10, -8, -8, -6},
        { -4, -6, -6, -8, -8, -6, -6, -4},
        { -2, -4, -4, -4, -4, -4, -4, -2},
        {  4,  4,  0,  0,  0,  0,  4,  4 },
        {  4,  6,  2,  0,  0,  2,  6,  4 }
    };

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            pawnValues[i][j] = pawn[i][j];
            knightValues[i][j] = knight[i][j];
            bishopValues[i][j] = bishop[i][j];
            rookValues[i][j] = rook[i][j];
            queenValues[i][j] = queen[i][j];
            kingValues[i][j] = king[i][j];
        }
    }
}


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
        // Maximize value of board on the AI's turn
        int maxValue = 0;
        for(std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int>::iterator it = validMoves.begin(); it != validMoves.end(); it++) {
            Chessboard tempBoard = board;
            tempBoard.move(color, it->first.first, it->first.second, true);
            value = getValueOfBoard(tempBoard);

            if((depth + 1 < 3 && value > currentValue) || (depth + 1 < 2 && value >= currentValue)) {
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
        // Minimize value of board on the player's turn
        int minValue = 0;
        for(std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int>::iterator it = validMoves.begin(); it != validMoves.end(); it++) {
            Chessboard tempBoard = board;
            tempBoard.move(playerColor, it->first.first, it->first.second, true);
            value = getValueOfBoard(tempBoard);

            if((depth + 1 < 3 && value < currentValue) || (depth + 1 < 2 && value <= currentValue)) {
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
                    sum += getValueOfPiece(p, i, j);
                }
                else {
                    sum -= getValueOfPiece(p, i, j);
                }
            }
        }
    }
    return sum;
}

// Returns the point value of a piece at a given x and y coordinate
int ChessAI::getValueOfPiece(Piece* piece, int x, int y) {
    if(piece == nullptr) {
        return 0;
    }
    if(piece->color == "white") {
        if(piece->type == "pawn") {
            return 10 + pawnValues[7-y][x];
        }
        else if(piece->type == "knight") {
            return 30 + knightValues[7-y][x];
        }
        else if(piece->type == "bishop") {
            return 30 + bishopValues[7-y][x];
        }
        else if(piece->type == "rook") {
            return 50 + rookValues[7-y][x];
        }
        else if(piece->type == "queen") {
            return 90 + queenValues[7-y][x];
        }
        else if(piece->type == "king") {
            return 1000 + kingValues[7-y][x];
        }
        else {
            return 0;
        }
    }
    else {
        if(piece->type == "pawn") {
            return 10 + pawnValues[y][7-x];
        }
        else if(piece->type == "knight") {
            return 30 + knightValues[y][7-x];
        }
        else if(piece->type == "bishop") {
            return 30 + bishopValues[y][7-x];
        }
        else if(piece->type == "rook") {
            return 50 + rookValues[y][7-x];
        }
        else if(piece->type == "queen") {
            return 90 + queenValues[y][7-x];
        }
        else if(piece->type == "king") {
            return 1000 + kingValues[y][7-x];
        }
        else {
            return 0;
        }
    }

 }