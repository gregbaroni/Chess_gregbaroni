#include "chessboard.hpp"

// Default constructor initializes the chessboard
Chessboard::Chessboard() {
    isWhiteInCheck = false;
    isBlackInCheck = false;
    isWhiteInCheckmate = false;
    isBlackInCheckmate = false;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j<8; j++) {
            board[i][j] = nullptr;
        }
    }

    for(int i = 0; i < 8; i++) {
        add_piece("white", "pawn", i, 1);
    }
    add_piece("white", "rook", 0, 0);
    add_piece("white", "rook", 7, 0);
    add_piece("white", "knight", 1, 0);
    add_piece("white", "knight", 6, 0);
    add_piece("white", "bishop", 2, 0);
    add_piece("white", "bishop", 5, 0);
    add_piece("white", "queen", 3, 0);
    add_piece("white", "king", 4, 0);

    for(int i = 0; i < 8; i++) {
        add_piece("black", "pawn", i, 6);
    }
    add_piece("black", "rook", 0, 7);
    add_piece("black", "rook", 7, 7);
    add_piece("black", "knight", 1, 7);
    add_piece("black", "knight", 6, 7);
    add_piece("black", "bishop", 2, 7);
    add_piece("black", "bishop", 5, 7);
    add_piece("black", "queen", 3, 7);
    add_piece("black", "king", 4, 7);
}


// Prints the current state of the board
void Chessboard::print_board() {
    for(int j = 7; j >= 0; j--) {
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
}

// Adds a piece to the board at the specified xcord and ycord
// Type specifies which type of piece to add
// Color specifies the color of the piece being added
void Chessboard::add_piece(std::string color, std::string type, int xcord, int ycord) {
    Piece* p = new Piece(color, type);
    board[xcord][ycord] = p;
}