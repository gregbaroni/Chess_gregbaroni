#include "chessboard.hpp"
#include <iostream>
#include <string>

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
                cout << "Start space: ";
                cin >> startSpace;
                valid = chessboard.validSpace(startSpace);
            }
            while(!valid);

            do {
                cout << "End space: ";
                cin >> endSpace;
                valid = chessboard.validSpace(endSpace);
            }
            while(!valid);

            valid = chessboard.move(player, startSpace, endSpace);
        }
        while(!valid);
        cout<<endl;
    }

    return 0;
}