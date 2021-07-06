#include "chessAI.hpp"

// Function that generates the next move for the ai
// Currently just picks a move at random
// Returns the move as a string in the form of "a3 a4"
std::string ChessAI::getNextMove(Chessboard& board) {
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> validMoves;
    if(color == "white") {
        validMoves = board.getWhiteValidMoves();
    }
    else {
        validMoves = board.getBlackValidMoves();
    }

    int size = validMoves.size();

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, size);

    int moveNumber = distr(gen);

    std::pair<std::pair<int,int>, std::pair<int,int>> move;
    int i = 0;
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int>::iterator it = validMoves.begin();
    while(i != moveNumber - 1) {
        i++;
        it++;
    }

    move = it->first;

    return convertMove(move);
}

// Converts the move from a pair of coordinates to a string of the form "e3 f4"
std::string ChessAI::convertMove(std::pair<std::pair<int,int>, std::pair<int,int>> move) {
    int x_startSpace = move.first.first;
    int y_startSpace = move.first.second;
    int x_endSpace = move.second.first;
    int y_endSpace = move.second.second;
    std::string result = "";

    result = result + convertToLetter(x_startSpace);
    result = result + std::to_string(y_startSpace + 1);
    result = result + " ";
    result = result + convertToLetter(x_endSpace);
    result = result + std::to_string(y_endSpace + 1);

    return result;
}

// Converts a number to the corresponding letter on the board
std::string ChessAI::convertToLetter(int n) {
    switch(n) {
        case 0:
            return "a";
            break;
        case 1:
            return "b";
            break;
        case 2:
            return "c";
            break;
        case 3:
            return "d";
            break;
        case 4:
            return "e";
            break;
        case 5:
            return "f";
            break;
        case 6:
            return "g";
            break;
        case 7:
            return "h";
            break;
        default:
            std::cout << "Unexpected number, exiting program" << std::endl;
            exit(1);
    }
    return "error";
}