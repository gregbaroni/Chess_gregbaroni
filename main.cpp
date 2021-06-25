#include "chessboard.hpp"
#include <iostream>
#include <string>
#include <limits>

using namespace std;

int main() {
    Chessboard chessboard;
    int turnCounter = 0;
    string startSpace;
    string endSpace;
    string player;
    bool valid = true;

    while(!chessboard.getIsWhiteInCheckmate() && !chessboard.getIsBlackInCheckmate() && !chessboard.getIsStalemate()) {
        chessboard.printBoard();
        cout << endl;

        turnCounter++;
        if(turnCounter % 2 == 1) {
            cout << "White's turn:" << endl;
            player = "white";
        }
        else {
            cout << "Black's turn:" << endl;
            player = "black";
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

    return 0;
}