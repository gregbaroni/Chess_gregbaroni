#include "chessboard.hpp"
#include "chessAI.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <utility>

using namespace std;


bool validResponse(string answer);

pair<int,int> convertFromBoardSpaceToCoords(string move);
string convertFromCoordsToBoardSpace(pair<int,int> coords);

int convertToNumber(char c);
string convertToLetter(int n);

int main() {
    Chessboard chessboard;
    int turnCounter = 0;
    string startSpace;
    string endSpace;
    string player;
    pair<int,int> startCoords;
    pair<int,int> endCoords;
    bool valid = true;

    string answer;

    do {
        cout << "2p game or vs AI?" << endl;
        cin >> answer;
        valid = validResponse(answer);
        if(!valid) {
            cin.clear();
            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');            
        }
    } while(!valid);
    cout << endl;

    // 2 player game
    if(answer == "2p") {
        while(!chessboard.getIsWhiteInCheckmate() && !chessboard.getIsBlackInCheckmate() && !chessboard.getIsStalemate()) {
            chessboard.printBoard();
            cout << endl;

            turnCounter++;
            if(turnCounter % 2 == 1) {
                cout << "White's turn" << endl;
                player = "white";
                if(chessboard.getIsWhiteInCheck()) {
                    cout << "White is in Check" << endl;
                }
            }
            else {
                cout << "Black's turn" << endl;
                player = "black";
                if(chessboard.getIsBlackInCheck()) {
                    cout << "Black is in Check" << endl;
                }
            }
            do {
                do {
                    cout << "Enter move: ";
                    cin >> startSpace;
                    valid = chessboard.validSpace(startSpace, 0);
                    if(!valid) {
                        cin.clear();
                        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                while(!valid);
                do {
                    cin >> endSpace;
                    valid = chessboard.validSpace(endSpace, 1);
                    if(!valid) {
                        cin.clear();
                        cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
                while(!valid);
                startCoords = convertFromBoardSpaceToCoords(startSpace);
                endCoords = convertFromBoardSpaceToCoords(endSpace);
                valid = chessboard.move(player, startCoords, endCoords);
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
            }
            while(!valid);
            cout<<endl;
        }
        chessboard.printBoard();
        cout << endl;
        // Check to see if someone won or if it is a tie
        if(chessboard.getIsWhiteInCheckmate()) {
            cout << "Checkmate" << endl;
            cout << "Black wins!" << endl;
        }
        else if(chessboard.getIsBlackInCheckmate()) {
            cout << "Checkmate" << endl;
            cout << "White wins!" << endl;
        }
        else if(chessboard.getIsStalemate()) {
            cout << "Stalemate" << endl;
        }
    }
    // Versus AI
    else {
        do {
            cout << "Choose to play as white or black?" << endl;
            cin >> answer;
            for(int i = 0; i < answer.length(); i++) {
                answer[i] = tolower(answer[i]);
            }
            if(answer != "white" && answer != "black") {
                cout << "Invalid response: enter white or black" << endl;
                valid = false;
            }
            else {
                valid = true;
            }
            if(!valid) {
                cin.clear();
                cin.ignore(numeric_limits<std::streamsize>::max(), '\n');            
            }
        } while(!valid);
        cout << endl;

        player = answer;
        string aiColor;
        bool aiTurn;
        std::pair<std::pair<int,int>, std::pair <int,int>>  move;
        if(player == "white") {
            aiColor = "black";
            aiTurn = false;
        }
        else {
            aiColor = "white";
            aiTurn = true;
        }

        ChessAI AI(aiColor);


        while(!chessboard.getIsWhiteInCheckmate() && !chessboard.getIsBlackInCheckmate() && !chessboard.getIsStalemate()) {
            chessboard.printBoard();
            cout << endl;

            turnCounter++;
            if(turnCounter % 2 == 1) {
                cout << "White's turn" << endl;
                if(chessboard.getIsWhiteInCheck()) {
                    cout << "White is in Check" << endl;
                }
            }
            else {
                cout << "Black's turn" << endl;
                if(chessboard.getIsBlackInCheck()) {
                    cout << "Black is in Check" << endl;
                }
            }

            std::string m;
            // Player's turn
            if(!aiTurn) {
                do {
                    do {
                        cout << "Enter move: ";
                        cin >> startSpace;
                        valid = chessboard.validSpace(startSpace, 0);
                        if(!valid) {
                            cin.clear();
                            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                        }
                    }
                    while(!valid);
                    do {
                        cin >> endSpace;
                        valid = chessboard.validSpace(endSpace, 1);
                        if(!valid) {
                            cin.clear();
                            cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                        }
                    }
                    while(!valid);
                    startCoords = convertFromBoardSpaceToCoords(startSpace);
                    endCoords = convertFromBoardSpaceToCoords(endSpace);
                    valid = chessboard.move(player, startCoords, endCoords);
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                }
                while(!valid);
                cout<<endl;
            }

            // AI's turn
            else if(aiTurn) {
                move = AI.getNextMove(chessboard);
                startCoords = move.first;
                endCoords = move.second;
                startSpace = convertFromCoordsToBoardSpace(startCoords);
                endSpace = convertFromCoordsToBoardSpace(endCoords);
                cout << "The AI's move is: " << startSpace << " " << endSpace << endl;
                chessboard.move(aiColor, startCoords, endCoords);
                cout<<endl;
            }

            aiTurn = !aiTurn;
        }

        chessboard.printBoard();
        cout << endl;
        // Check to see if someone won or if it is a tie
        if(chessboard.getIsWhiteInCheckmate()) {
            cout << "Checkmate" << endl;
            cout << "Black wins!" << endl;
        }
        else if(chessboard.getIsBlackInCheckmate()) {
            cout << "Checkmate" << endl;
            cout << "White wins!" << endl;
        }
        else if(chessboard.getIsStalemate()) {
            cout << "Stalemate" << endl;
        }
    }

    return 0;
}


// Checks to see if the user inputted either "2p" or "ai"
bool validResponse(string answer) {
    for(int i = 0; i < answer.length(); i++) {
        if(isalpha(answer[i]))
            answer[i] = tolower(answer[i]);
    }
    if(answer != "2p" && answer != "ai") {
        cout << "Invalid response: enter 2p or AI" << endl;
        return false;
    }
    return true;
}


// Converts the user inputted space, such as "a3", to it's corresponding coordinates on the board
std::pair<int,int> convertFromBoardSpaceToCoords(string move) {
    int x = convertToNumber(move[0]);
    int y = move[1] - '1';
    return make_pair(x,y);
}

//Converts the coordinates of the AI's move into the format of "e2"
string convertFromCoordsToBoardSpace(pair<int,int> coords) {
    string result = "";
    result = result + convertToLetter(coords.first) + to_string(coords.second+1);
    return result;
}

// Converts a letter between a and h to its corresponding index on the chessboard
int convertToNumber(char c) {
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

// converts a number between 0 and 7 to its corresponding letter on the chessboard
string convertToLetter(int n) {
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