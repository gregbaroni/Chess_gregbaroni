#include "chessboard.hpp"

// Default constructor initializes the chessboard
Chessboard::Chessboard() {
    isWhiteInCheck = false;
    isBlackInCheck = false;
    isWhiteInCheckmate = false;
    isBlackInCheckmate = false;

    std::vector<std::pair <int,int>> v1;
    std::vector<std::pair <int,int>> v2;
    whiteValidMoves = v1;
    blackValidMoves = v2;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j<8; j++) {
            board[i][j] = nullptr;
        }
    }

    for(int i = 0; i < 8; i++) {
        addPiece("white", "pawn", i, 1);
    }
    addPiece("white", "rook", 0, 0);
    addPiece("white", "rook", 7, 0);
    addPiece("white", "knight", 1, 0);
    addPiece("white", "knight", 6, 0);
    addPiece("white", "bishop", 2, 0);
    addPiece("white", "bishop", 5, 0);
    addPiece("white", "queen", 3, 0);
    addPiece("white", "king", 4, 0);

    for(int i = 0; i < 8; i++) {
        addPiece("black", "pawn", i, 6);
    }
    addPiece("black", "rook", 0, 7);
    addPiece("black", "rook", 7, 7);
    addPiece("black", "knight", 1, 7);
    addPiece("black", "knight", 6, 7);
    addPiece("black", "bishop", 2, 7);
    addPiece("black", "bishop", 5, 7);
    addPiece("black", "queen", 3, 7);
    addPiece("black", "king", 4, 7);

    std::pair <int,int> whiteKing(4,0);
    std::pair <int,int> blackKing(4,7);

    calculateValidMoves();
}


// Prints the current state of the board
void Chessboard::printBoard() {
    for(int j = 7; j >= 0; j--) {
        std::cout << " " << j + 1 << " |";
        for(int i = 0; i < 8; i++) {
            if(board[i][j] == nullptr) {
                std::cout << " * ";
            }
            else {
                Piece p = *(board[i][j]);
                if(p.color == "white") {
                    if(p.type == "pawn") {
                        std::cout << " p ";
                    }
                    else if(p.type == "rook") {
                        std::cout << " r ";
                    }
                    else if(p.type == "knight") {
                        std::cout << " n ";
                    }
                    else if(p.type == "bishop") {
                        std::cout << " b ";
                    }
                    else if(p.type == "queen") {
                        std::cout << " q ";
                    }
                    else {
                        std::cout << " k ";
                    }
                }
                else {
                    if(p.type == "pawn") {
                        std::cout << " P ";
                    }
                    else if(p.type == "rook") {
                        std::cout << " R ";
                    }
                    else if(p.type == "knight") {
                        std::cout << " N ";
                    }
                    else if(p.type == "bishop") {
                        std::cout << " B ";
                    }
                    else if(p.type == "queen") {
                        std::cout << " Q ";
                    }
                    else {
                        std::cout << " K ";
                    }
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "     ——————————————————————" << std::endl;
    std::string alphabet = "abcdefgh";
    std::cout << "    ";
    for(int i = 0; i < 8; i++) {
        std::cout << " " << alphabet[i] << " ";
    }
    std::cout << std::endl;
}

// Checks to see if the user inputted space is a valid space
// A valid space is a letter between a and h, followed by a number between 1 and 8
bool Chessboard::validSpace(std::string space) {
    if(space.length() != 2) {
        std::cout << "Invalid space syntax: space should be two characters long" << std::endl;;
        return false;
    }
    std::string alphabet = "abcdefgh";
    char c = space[0];
    if(alphabet.find(c) == std::string::npos) {
        std::cout << "Invalid space syntax: first character of the space should be a letter between a and h" << std::endl;
        return false;
    }
    std::string numbers = "12345678";
    char n = space[1];
    if(numbers.find(n) == std::string::npos) {
        std::cout << "Invalid space syntax: second character of the space should be a number between 1 and 8" << std::endl;
        return false;
    }
    return true;
}

// Function for carrying out a player's move
bool Chessboard::move(std::string player, std::string startSpace, std::string endSpace) {
    int x_startSpace, y_startSpace;
    int x_endSpace, y_endSpace;
    y_startSpace = startSpace[1] - '1';
    y_endSpace = endSpace[1] - '1';
    x_startSpace = convertToNumber(startSpace[0]);
    x_endSpace = convertToNumber(endSpace[0]);

    // TODO: check to see if the move is valid

    board[x_endSpace][y_endSpace] = board[x_startSpace][y_startSpace];
    board[x_startSpace][y_startSpace] = nullptr;

    calculateValidMoves();

    // TODO: check to see if the valid move causes an invalid gamestate, such as player's king now being in check
    
    return true;
}

// Function that recalculates the valid moves
// Called at the start of the match, and after every move
void Chessboard::calculateValidMoves() {

    // TODO: Need to store the valid moves of each piece to see if a move is valid
    //       and the valid moves for each player to see if there is a stalemate, checkmate, etc.
    return;
}


// Getter for isWhiteInCheckmate
bool Chessboard::getIsWhiteInCheckmate() {
    return isWhiteInCheckmate;
}

// Getter for isBlackInCheckmate
bool Chessboard::getIsBlackInCheckmate() {
    return isBlackInCheckmate;
}

// Getter for isStalemate
bool Chessboard::getIsStalemate() {
    return isStalemate;
}

// Adds a piece to the board at the specified xcord and ycord
// Type specifies which type of piece to add
// Color specifies the color of the piece being added
void Chessboard::addPiece(std::string color, std::string type, int xcord, int ycord) {
    Piece* p = new Piece(color, type);
    board[xcord][ycord] = p;
}

// Converts a letter between a and h to its corresponding index on the chessboard
int Chessboard::convertToNumber(char c) {
    switch(c) {
        case 'a':
            return 0;
            break;
        case 'b':
            return 1;
            break;
        case 'c':
            return 2;
            break;
        case 'd':
            return 3;
            break;
        case 'e':
            return 4;
            break;
        case 'f':
            return 5;
            break;
        case 'g':
            return 6;
            break;
        case 'h':
            return 7;
            break;
        default:
            std::cout << "Unexpected letter, exiting program" << std::endl;
            exit(1);
    }
    return -99;
}