#include "chessboard.hpp"
#include "chessAI.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <utility>

using namespace std;

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


int main() {
    Chessboard chessboard;
    int turnCounter = 0;
    string startSpace;
    string endSpace;
    string player;
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
                valid = chessboard.move(player, startSpace, endSpace);
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
        std::string move;
        if(player == "white") {
            aiColor = "black";
        }
        else {
            aiColor = "white";
        }

        ChessAI AI(aiColor);

        while(!chessboard.getIsWhiteInCheckmate() && !chessboard.getIsBlackInCheckmate() && !chessboard.getIsStalemate()) {
            chessboard.printBoard();
            cout << endl;

            turnCounter++;
            if(turnCounter % 2 == 1) {
                cout << "White's turn" << endl;
                if(player == "white") {
                    aiTurn = false;
                }
                else {
                    aiTurn = true;
                }
                if(chessboard.getIsWhiteInCheck()) {
                    cout << "White is in Check" << endl;
                }
            }
            else {
                cout << "Black's turn" << endl;
                if(player == "black") {
                    aiTurn = false;
                }
                else {
                    aiTurn = true;
                }
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
                    valid = chessboard.move(player, startSpace, endSpace);
                    cin.clear();
                    cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
                }
                while(!valid);
                cout<<endl;
            }

            // AI's turn
            else if(aiTurn) {
                move = AI.getNextMove(chessboard);
                startSpace = move.substr(0,2);
                endSpace = move.substr(3,2);
                cout << "The AI's move is: " << startSpace << " " << endSpace << endl;
                chessboard.move(aiColor, startSpace, endSpace);
                cout<<endl;
            }
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