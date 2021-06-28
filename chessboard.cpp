#include "chessboard.hpp"

// Default constructor initializes the chessboard
Chessboard::Chessboard() {
    isWhiteInCheck = false;
    isBlackInCheck = false;
    isWhiteInCheckmate = false;
    isBlackInCheckmate = false;
    isStalemate = false;

    std::map<std::pair <int,int>, int> v1;
    std::map<std::pair <int,int>, int> v2;
    whiteValidCaptures = v1;
    blackValidCaptures = v2;

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

    whiteKingPos = whiteKing;
    blackKingPos = blackKing;

    calculateValidMoves();
}

// Destructor for chessboard
Chessboard::~Chessboard() {
    deleteBoard();
}

// Copy constructor for chessboard
Chessboard::Chessboard(const Chessboard& source) {
    isWhiteInCheck = source.isWhiteInCheck;
    isBlackInCheck = source.isBlackInCheck;
    isWhiteInCheckmate = source.isWhiteInCheckmate;
    isBlackInCheckmate = source.isBlackInCheckmate;
    isStalemate = source.isStalemate;

    whiteKingPos = source.whiteKingPos;
    blackKingPos = source.blackKingPos;

    whiteValidCaptures = source.whiteValidCaptures;
    blackValidCaptures = source.blackValidCaptures;

    std::string color;
    std::string type;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(source.board[i][j] == nullptr) {
                board[i][j] == nullptr;
            }
            else {
                color = source.board[i][j]->color;
                type = source.board[i][j]->type;
                Piece* p = new Piece(color, type, source.board[i][j]->validMoves);
                board[i][j] = p;
            }
        }
    }
}

// Copy assignment operator for chessboard
Chessboard& Chessboard::operator=(const Chessboard& source) {
    deleteBoard();
    isWhiteInCheck = source.isWhiteInCheck;
    isBlackInCheck = source.isBlackInCheck;
    isWhiteInCheckmate = source.isWhiteInCheckmate;
    isBlackInCheckmate = source.isBlackInCheckmate;
    isStalemate = source.isStalemate;

    whiteKingPos = source.whiteKingPos;
    blackKingPos = source.blackKingPos;

    whiteValidCaptures = source.whiteValidCaptures;
    blackValidCaptures = source.blackValidCaptures;

    std::string color;
    std::string type;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(source.board[i][j] == nullptr) {
                board[i][j] == nullptr;
            }
            else {
                color = source.board[i][j]->color;
                type = source.board[i][j]->type;
                Piece* p = new Piece(color, type, source.board[i][j]->validMoves);
                board[i][j] = p;
            }
        }
    }
    return *this;
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
                    else if(p.type == "king") {
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
                    else if(p.type == "king") {
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
// s is 0 when it is checking a start space and s is 1 when it is checking an end space
bool Chessboard::validSpace(std::string space, int s) {
    if(space.length() != 2) {
        std::cout << "Invalid ";
        if(s) {
            std::cout << "end ";
        }
        else {
            std::cout << "start ";
        }
        std::cout << "space syntax: space should be two characters long" << std::endl;
        return false;
    }
    std::string alphabet = "abcdefgh";
    char c = space[0];
    if(alphabet.find(c) == std::string::npos) {
        std::cout << "Invalid ";
        if(s) {
            std::cout << "end ";
        }
        else {
            std::cout << "start ";
        }
        std::cout << "space syntax: first character of the space should be a letter between a and h" << std::endl;
        return false;
    }
    std::string numbers = "12345678";
    char n = space[1];
    if(numbers.find(n) == std::string::npos) {
        std::cout << "Invalid ";
        if(s) {
            std::cout << "end ";
        }
        else {
            std::cout << "start ";
        }
        std::cout << "space syntax: second character of the space should be a number between 1 and 8" << std::endl;
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

    Piece* p = board[x_startSpace][y_startSpace];
    std::pair<int,int> move;
    move = std::make_pair(x_endSpace, y_endSpace);

    if(p == nullptr) {
        std::cout << "Illegal move: there is no piece on that square" << std::endl;
        return false;
    }
    if(p->color != player) {
        std::cout << "Illegal move: that piece does not belong to you" << std::endl;
        return false;
    }
    if(p->validMoves.find(move) == p->validMoves.end()) {
        std::cout << "Illegal move: that piece is unable to move to that space" << std::endl;
        return false;
    }

    bool wasWhiteInCheck = isWhiteInCheck;
    bool wasBlackInCheck = isBlackInCheck;
    Piece* temp = board[x_endSpace][y_endSpace];
    std::map<std::pair <int,int>, int> tempWhiteValidCaptures = whiteValidCaptures;
    std::map<std::pair <int,int>, int> tempBlackValidCaptures = blackValidCaptures;

    std::string color;
    std::string type;
    Piece* tempBoard[8][8];
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] == nullptr) {
                tempBoard[i][j] == nullptr;
            }
            else {
                color = board[i][j]->color;
                type = board[i][j]->type;
                Piece* p2 = new Piece(color, type, board[i][j]->validMoves);
                tempBoard[i][j] = p2;
            }
        }
    }
    board[x_endSpace][y_endSpace] = board[x_startSpace][y_startSpace];
    board[x_startSpace][y_startSpace] = nullptr;
    if(p->type == "king") {
        if(player == "white") {
            whiteKingPos = move;
        }
        else {
            blackKingPos = move;
        }
    }

    calculateBoardState(player);

    if(player == "white") {
        if(isWhiteInCheck) {
            if(wasWhiteInCheck) {
                std::cout << "Illegal move: your king is in Check" << std::endl;
            }
            else {
                std::cout << "Illegal move: that move puts your king in Check" << std::endl;
            }

            board[x_endSpace][y_endSpace] = temp;
            board[x_startSpace][y_startSpace] = p;
            if(p->type == "king") {
                whiteKingPos = std::make_pair(x_startSpace, y_startSpace);
            }
            isWhiteInCheck = wasWhiteInCheck;
            isBlackInCheck = wasBlackInCheck;
            whiteValidCaptures = tempWhiteValidCaptures;
            blackValidCaptures = tempBlackValidCaptures;
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    if(tempBoard[i][j] == nullptr) {
                        board[i][j] == nullptr;
                    }
                    else {
                        color = tempBoard[i][j]->color;
                        type = tempBoard[i][j]->type;
                        Piece* p3 = new Piece(color, type, tempBoard[i][j]->validMoves);
                        if(board[i][j] != nullptr) {
                            delete board[i][j];
                        }
                        board[i][j] = p3;
                        delete tempBoard[i][j];
                    }
                }
            }
            return false;
        }
    }
    else {
        if(isBlackInCheck) {
            if(wasBlackInCheck) {
                std::cout << "Illegal move: your king is in Check" << std::endl;
            }
            else {
                std::cout << "Illegal move: that move puts your king in Check" << std::endl;
            }

            board[x_endSpace][y_endSpace] = temp;
            board[x_startSpace][y_startSpace] = p;
            if(p->type == "king") {
                blackKingPos = std::make_pair(x_startSpace, y_startSpace);
            }
            isWhiteInCheck = wasWhiteInCheck;
            isBlackInCheck = wasBlackInCheck;
            whiteValidCaptures = tempWhiteValidCaptures;
            blackValidCaptures = tempBlackValidCaptures;
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    if(tempBoard[i][j] == nullptr) {
                        board[i][j] == nullptr;
                    }
                    else {
                        color = tempBoard[i][j]->color;
                        type = tempBoard[i][j]->type;
                        Piece* p3 = new Piece(color, type, tempBoard[i][j]->validMoves);
                        if(board[i][j] != nullptr) {
                            delete board[i][j];
                        }
                        board[i][j] = p3;
                        delete tempBoard[i][j];
                    }
                }
            }
            return false;
        }
    }

    delete temp;
    /*
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(tempBoard2[i][j] != nullptr) {
                delete tempBoard2[i][j];
            }
        }
    }
    */
    return true;
}

// Function that recalculates the valid moves for each piece
// and checks to see if there is a checkmate, stalemenate, etc.
// Called after every move
void Chessboard::calculateBoardState(std::string player) {
    calculateValidMoves();
    calculateKingStates(player);
}

// Function that recalculates the valid moves
// Called at the start of the match and when checking for a checkmate, stalemate, etc.
void Chessboard::calculateValidMoves() {
    whiteValidCaptures.clear();
    blackValidCaptures.clear();
    Piece* p;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr) {
                p = board[i][j];
                p->validMoves.clear();
                if(p->type == "pawn") {
                    if(p->color == "white") {
                        if(j+1 < 8 && board[i][j+1] == nullptr) {
                            p->validMoves[std::make_pair(i,j+1)] = 1;
                        }
                        if(j == 1 && board[i][j+1] == nullptr && board[i][j+2] == nullptr) {
                            p->validMoves[std::make_pair(i,j+2)] = 1;
                        }
                        if(j+1 < 8 && i+1 < 8 && board[i+1][j+1] != nullptr && board[i+1][j+1]->color == "black") {
                            p->validMoves[std::make_pair(i+1,j+1)] = 1;
                            whiteValidCaptures[std::make_pair(i+1,j+1)] = 1;                          
                        }
                        if(j+1 < 8 && i-1 >= 0 && board[i-1][j+1] != nullptr && board[i-1][j+1]->color == "black") {
                            p->validMoves[std::make_pair(i-1,j+1)] = 1;
                            whiteValidCaptures[std::make_pair(i-1,j+1)] = 1;                                
                        }
                    }
                    else {
                        if(j-1 >= 0 && board[i][j-1] == nullptr) {
                            p->validMoves[std::make_pair(i,j-1)] = 1;
                        }
                        if(j == 6 && board[i][j-1] == nullptr && board[i][j-2] == nullptr) {
                            p->validMoves[std::make_pair(i,j-2)] = 1;
                        }
                        if(j-1 >= 0 && i+1 < 8 && board[i+1][j-1] != nullptr && board[i+1][j-1]->color == "white") {
                            p->validMoves[std::make_pair(i+1,j-1)] = 1;
                            blackValidCaptures[std::make_pair(i+1,j-1)] = 1;                          
                        }
                        if(j-1 >= 0 && i-1 >= 0 && board[i-1][j-1] != nullptr && board[i-1][j-1]->color == "white") {
                            p->validMoves[std::make_pair(i-1,j-1)] = 1;
                            blackValidCaptures[std::make_pair(i-1,j-1)] = 1;                                
                        }
                    }
                    // TODO: Implement en passant
                    // TODO: Implement pawn reaching end of the board
                }
                else if(p->type == "rook") {
                    // Vertical movement
                    int y = j+1;
                    while(y < 8 && board[i][y] == nullptr) {
                        p->validMoves[std::make_pair(i,y)] = 1;
                        y++;
                    }
                    if(y < 8) {
                        validCapture(p,i,y);
                    }
                    y = j-1;
                    while(y >= 0 && board[i][y] == nullptr) {
                        p->validMoves[std::make_pair(i,y)] = 1;
                        y--;
                    }
                    if(y >= 0) {
                        validCapture(p,i,y);
                    }
                    // Horizontal movement
                    int x = i+1;
                    while(x < 8 && board[x][j] == nullptr) {
                        p->validMoves[std::make_pair(x,j)] = 1;
                        x++;
                    }
                    if(x < 8) {
                        validCapture(p,x,j);
                    }
                    x = i-1;
                    while(x >= 0 && board[x][j] == nullptr) {
                        p->validMoves[std::make_pair(x,j)] = 1;
                        x--;
                    }
                    if(x >= 0) {
                        validCapture(p,x,j);
                    }
                }
                else if(p->type == "knight") {
                    int x, y;
                    std::vector<std::pair<int,int>> v;
                    v.push_back(std::make_pair(i-1,j+2));
                    v.push_back(std::make_pair(i+1,j+2));
                    v.push_back(std::make_pair(i-1,j-2));
                    v.push_back(std::make_pair(i+1,j-2));
                    v.push_back(std::make_pair(i+2,j-1));
                    v.push_back(std::make_pair(i+2,j+1));
                    v.push_back(std::make_pair(i-2,j-1));
                    v.push_back(std::make_pair(i-2,j+1));
                    for(int k = 0; k < v.size(); k++) {
                        x = v[k].first;
                        y = v[k].second;
                        if(x >= 0 && x < 8 && y >= 0 && y < 8) {
                            if(board[x][y] == nullptr) {
                                p->validMoves[std::make_pair(x,y)] = 1;
                            }
                            else {
                                validCapture(p,x,y);
                            }
                        }
                    }
                }
                else if(p->type == "bishop") {
                    // 45 degree angle movement
                    int x = i+1;
                    int y = j+1;
                    while(x < 8 && y < 8 && board[x][y] == nullptr) {
                        p->validMoves[std::make_pair(x,y)] = 1;
                        x++;
                        y++;
                    }
                    if(x < 8 && y < 8) {
                        validCapture(p,x,y);
                    }
                    x = i-1;
                    y = j-1;
                    while(x >= 0 && y >= 0 && board[x][y] == nullptr) {
                        p->validMoves[std::make_pair(x,y)] = 1;
                        x--;
                        y--;
                    }
                    if(x >= 0 && y >= 0) {
                        validCapture(p,x,y);
                    }
                    // 135 degree angle movment
                    x = i+1;
                    y = j-1;
                    while(x < 8 && y >= 0 && board[x][y] == nullptr) {
                        p->validMoves[std::make_pair(x,y)] = 1;
                        x++;
                        y--;
                    }
                    if(x < 8 && y >= 0) {
                        validCapture(p,x,y);
                    }
                    x = i-1;
                    y = j+1;
                    while(x >= 0 && y < 8 && board[x][y] == nullptr) {
                        p->validMoves[std::make_pair(x,y)] = 1;
                        x--;
                        y++;
                    }
                    if(x >= 0 && y < 8) {
                        validCapture(p,x,y);
                    }
                }
                else if(p->type == "queen") {
                    // Vertical movement
                    int y = j+1;
                    while(y < 8 && board[i][y] == nullptr) {
                        p->validMoves[std::make_pair(i,y)] = 1;
                        y++;
                    }
                    if(y < 8) {
                        validCapture(p,i,y);
                    }
                    y = j-1;
                    while(y >= 0 && board[i][y] == nullptr) {
                        p->validMoves[std::make_pair(i,y)] = 1;
                        y--;
                    }
                    if(y >= 0) {
                        validCapture(p,i,y);
                    }
                    // Horizontal movement
                    int x = i+1;
                    while(x < 8 && board[x][j] == nullptr) {
                        p->validMoves[std::make_pair(x,j)] = 1;
                        x++;
                    }
                    if(x < 8) {
                        validCapture(p,x,j);
                    }
                    x = i-1;
                    while(x >= 0 && board[x][j] == nullptr) {
                        p->validMoves[std::make_pair(x,j)] = 1;
                        x--;
                    }
                    if(x >= 0) {
                        validCapture(p,x,j);
                    }
                    // 45 degree angle movement
                    x = i+1;
                    y = j+1;
                    while(x < 8 && y < 8 && board[x][y] == nullptr) {
                        p->validMoves[std::make_pair(x,y)] = 1;
                        x++;
                        y++;
                    }
                    if(x < 8 && y < 8) {
                        validCapture(p,x,y);
                    }
                    x = i-1;
                    y = j-1;
                    while(x >= 0 && y >= 0 && board[x][y] == nullptr) {
                        p->validMoves[std::make_pair(x,y)] = 1;
                        x--;
                        y--;
                    }
                    if(x >= 0 && y >= 0) {
                        validCapture(p,x,y);
                    }
                    // 135 degree angle movment
                    x = i+1;
                    y = j-1;
                    while(x < 8 && y >= 0 && board[x][y] == nullptr) {
                        p->validMoves[std::make_pair(x,y)] = 1;
                        x++;
                        y--;
                    }
                    if(x < 8 && y >= 0) {
                        validCapture(p,x,y);
                    }
                    x = i-1;
                    y = j+1;
                    while(x >= 0 && y < 8 && board[x][y] == nullptr) {
                        p->validMoves[std::make_pair(x,y)] = 1;
                        x--;
                        y++;
                    }
                    if(x >= 0 && y < 8) {
                        validCapture(p,x,y);
                    }
                }
                else if(p->type == "king") {
                    int x, y;
                    std::vector<std::pair<int,int>> v;
                    v.push_back(std::make_pair(i,j+1));
                    v.push_back(std::make_pair(i,j-1));
                    v.push_back(std::make_pair(i+1,j));
                    v.push_back(std::make_pair(i-1,j));
                    v.push_back(std::make_pair(i+1,j+1));
                    v.push_back(std::make_pair(i+1,j-1));
                    v.push_back(std::make_pair(i-1,j+1));
                    v.push_back(std::make_pair(i-1,j-1));
                    for(int k = 0; k < v.size(); k++) {
                        x = v[k].first;
                        y = v[k].second;
                        if(x >= 0 && x < 8 && y >= 0 && y < 8) {
                            if(board[x][y] == nullptr) {
                                p->validMoves[std::make_pair(x,y)] = 1;
                            }
                            else {
                                validCapture(p,x,y);
                            }
                        }
                    }

                    //TODO: Implement castling
                }
            }
        }
    }

    return;
}

// Checks to see if the kings are in check, checkmate, or if there is a stalemate
// Called after every move by calculateBoardState
void Chessboard::calculateKingStates(std::string player) {
    if(whiteValidCaptures.find(blackKingPos) != whiteValidCaptures.end()) {
        isBlackInCheck = true;
    }
    else {
        isBlackInCheck = false;
    }
    if(blackValidCaptures.find(whiteKingPos) != blackValidCaptures.end()) {
        isWhiteInCheck = true;
    }
    else {
        isWhiteInCheck = false;
    }

    // Check each valid move to see if it places king in check
    bool moveExistsForWhite = false;
    bool moveExistsForBlack = false;
    Piece* p;
    Piece* temp;
    std::vector<Piece> oldBoard;
    std::vector<std::pair<int,int>> coords;
    std::string color;
    std::string type;
    bool wasWhiteInCheck;
    bool wasBlackInCheck;
    std::map<std::pair <int,int>, int> tempWhiteValidCaptures;
    std::map<std::pair <int,int>, int> tempBlackValidCaptures;
    std::map<std::pair <int,int>, int> moves;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr && ((!moveExistsForWhite && board[i][j]->color == "white") || (!moveExistsForBlack && board[i][j]->color == "black"))) {         
                p = board[i][j];
                moves = p->validMoves;
                for(std::map<std::pair <int,int>, int>::iterator it = moves.begin(); it != moves.end(); it++) {
                    temp = board[it->first.first][it->first.second];
                    wasWhiteInCheck = isWhiteInCheck;
                    wasBlackInCheck = isBlackInCheck;
                    tempWhiteValidCaptures = whiteValidCaptures;
                    tempBlackValidCaptures = blackValidCaptures;

                    for(int k = 0; k < 8; k++) {
                        for(int l = 0; l < 8; l++) {
                            if(board[k][l] != nullptr) {
                                color = board[k][l]->color;
                                type = board[k][l]->type;
                                Piece p2(color, type, board[k][l]->validMoves);
                                oldBoard.push_back(p2);
                                coords.push_back(std::make_pair(k,l));
                            }
                        }
                    }

                    board[it->first.first][it->first.second] = board[i][j];
                    board[i][j] = nullptr;
                    if(p->type == "king") {
                        if(p->color == "white") {
                            whiteKingPos = std::make_pair(it->first.first, it->first.second);
                        }
                        else {
                            blackKingPos = std::make_pair(it->first.first, it->first.second);
                        }
                    }

                    calculateValidMoves();

                    if(p->color == "white") {
                        if(!isWhiteInCheck) {
                            moveExistsForWhite = true;
                        }
                        if(p->type == "king") {
                            whiteKingPos = std::make_pair(i, j);
                        }
                    }
                    else {
                        if(!isBlackInCheck) {
                            moveExistsForBlack = true;
                        }
                        if(p->type == "king") {
                            blackKingPos = std::make_pair(i, j);
                        }
                    }

                    board[it->first.first][it->first.second] = temp;
                    board[i][j] = p;

                    isWhiteInCheck = wasWhiteInCheck;
                    isBlackInCheck = wasBlackInCheck;
                    whiteValidCaptures = tempWhiteValidCaptures;
                    blackValidCaptures = tempBlackValidCaptures;
                    
                    for(int k = 0; k < oldBoard.size(); k++) {
                        int x = coords[k].first;
                        int y = coords[k].second;
                        board[x][y]->validMoves = oldBoard[k].validMoves;
                    }               
                }
            }
        }
    }
    if(isWhiteInCheck) {
        if(moveExistsForWhite) {
            isWhiteInCheckmate = false;
        }
        else {
            isWhiteInCheckmate = true;
        }
    }
    if(isBlackInCheck) {
        if(moveExistsForBlack) {
            isBlackInCheckmate = false;
        }
        else {
            isBlackInCheckmate = true;
        }
    }

    if(player == "white") {
        if(!moveExistsForBlack) {
            isStalemate = true;
        }
        else {
            isStalemate = false;
        }
    }
    else {
        if(!moveExistsForWhite) {
            isStalemate = true;
        }
        else {
            isStalemate = false;
        }
    }
}

// Getter for isWhiteInCheck
bool Chessboard::getIsWhiteInCheck() {
    return isWhiteInCheck;
}

// Getter for isBlackInCheck
bool Chessboard::getIsBlackInCheck() {
    return isBlackInCheck;
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

// Sees if a capture is valid and, if so, adds it to the validMoves and validCaptures maps
void Chessboard::validCapture(Piece* p, int x, int y) {
    if(board[x][y]->color != p->color) {
        p->validMoves[std::make_pair(x,y)] = 1;
        if(p->color == "white") {
            whiteValidCaptures[std::make_pair(x,y)] = 1;
        }
        else {
            blackValidCaptures[std::make_pair(x,y)] = 1;
        }
    }    
}

// Clears the board
void Chessboard::deleteBoard() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr) {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
    }
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