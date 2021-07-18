#include "chessboard.hpp"


// Default constructor initializes the chessboard
Chessboard::Chessboard() {
    isWhiteInCheck = false;
    isBlackInCheck = false;
    isWhiteInCheckmate = false;
    isBlackInCheckmate = false;
    isStalemate = false;
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> v1;
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> v2;
    whitePossibleMoves = v1;
    blackPossibleMoves = v2;
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> v3;
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> v4;
    whiteValidMoves = v3;
    blackValidMoves = v4;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
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

    calculateBoardState("black");
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

    whitePossibleMoves = source.whitePossibleMoves;
    blackPossibleMoves = source.blackPossibleMoves;
    whiteValidMoves = source.whiteValidMoves;
    blackValidMoves = source.blackValidMoves;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }
    }

    std::string color;
    std::string type;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(source.board[i][j] != nullptr) {
                color = source.board[i][j]->color;
                type = source.board[i][j]->type;
                addPiece(color, type, i, j);
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

    whitePossibleMoves = source.whitePossibleMoves;
    blackPossibleMoves = source.blackPossibleMoves;
    whiteValidMoves = source.whiteValidMoves;
    blackValidMoves = source.blackValidMoves;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            board[i][j] = nullptr;
        }
    }

    std::string color;
    std::string type;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(source.board[i][j] != nullptr) {
                color = source.board[i][j]->color;
                type = source.board[i][j]->type;
                addPiece(color, type, i, j);
            }
        }
    }
    
    return *this;
}


// Prints the current state of the board
// Uppercase letters for black, lowercase letters for white
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
// Input is the color of the piece that is moving, and the start space and endspace
// Start space and end space are strings of the form "e3" or "a6"
// aiTurn is a boolean value to determine if the move belongs to a player or to the ai
bool Chessboard::move(std::string player, std::pair<int,int> startSpace, std::pair<int,int> endSpace, bool aiTurn) {
    // convert start space and end space to numbers
    int x_startSpace, y_startSpace;
    int x_endSpace, y_endSpace;
    x_startSpace = startSpace.first;
    y_startSpace = startSpace.second;
    x_endSpace = endSpace.first;
    y_endSpace = endSpace.second;

    Piece* p = board[x_startSpace][y_startSpace];
    std::pair<int,int> startCoords = std::make_pair(x_startSpace, y_startSpace);
    std::pair<int,int> endCoords = std::make_pair(x_endSpace, y_endSpace);
    std::pair<std::pair<int,int>, std::pair <int,int>> move = std::make_pair(startCoords, endCoords);

    // Check to see if move is valid
    if(!aiTurn) {
        if(p == nullptr) {
            std::cout << "Illegal move: there is no piece on that square" << std::endl;
            return false;
        }
        if(p->color != player) {
            std::cout << "Illegal move: that piece does not belong to you" << std::endl;
            return false;
        }
        if(player == "white") {
            if(whitePossibleMoves.find(move) == whitePossibleMoves.end()) {
                // Check if the player is attempting to castle
                if(p->type == "king") {
                    if(x_startSpace == 4 && y_startSpace == 0) {
                        if((x_endSpace == 6 && y_endSpace == 0) ||(x_endSpace == 2 && y_endSpace == 0)) {
                            std::cout << "Illegal move: the king is unable to castle" << std::endl;
                            return false;
                        }
                    }               
                }
                std::cout << "Illegal move: that piece is unable to move to that space" << std::endl;
                return false;
            }
            // Move is possible but not legal
            if(whiteValidMoves.find(move) == whiteValidMoves.end()) {
                if(isWhiteInCheck) {
                    std::cout << "Illegal move: your king is in Check" << std::endl;
                    return false;
                }
                else {
                    std::cout << "Illegal move: that move puts your king in Check" << std::endl;
                    return false;
                }
            }
        }
        else {
            if(blackPossibleMoves.find(move) == blackPossibleMoves.end()) {
                // Check if the player is attempting to castle
                if(p->type == "king") {
                    if(x_startSpace == 4 && y_startSpace == 7) {
                        if((x_endSpace == 6 && y_endSpace == 7) ||(x_endSpace == 2 && y_endSpace == 7)) {
                            std::cout << "Illegal move: the king is unable to castle" << std::endl;
                            return false;
                        }
                    }           
                }
                std::cout << "Illegal move: that piece is unable to move to that space" << std::endl;
                return false;
            }
            // Move is possible but not legal
            if(blackValidMoves.find(move) == blackValidMoves.end()) {
                if(isBlackInCheck) {
                    std::cout << "Illegal move: your king is in Check" << std::endl;
                    return false;
                }
                else {
                    std::cout << "Illegal move: that move puts your king in Check" << std::endl;
                    return false;
                }
            }
        }
    }


    Piece* temp = board[x_endSpace][y_endSpace];

    bool enPassant = false;
    // Check if en passant
    if(p->type == "pawn" && temp == nullptr && x_startSpace != x_endSpace) {
        // En passant is when a pawn takes another pawn that just double moved by moving to the space it skipped
        // Only capture where the space the attacking piece ends on is not where the captured piece is
        board[x_endSpace][y_endSpace] = board[x_startSpace][y_startSpace];
        board[x_startSpace][y_startSpace] = nullptr;
        if(p->color == "white") {
            temp = board[x_endSpace][y_endSpace-1];
            board[x_endSpace][y_endSpace-1] = nullptr;
        }   
        else {
            temp = board[x_endSpace][y_endSpace+1];
            board[x_endSpace][y_endSpace+1] = nullptr;
        }     
        enPassant = true;
    }
    else {
        // Regular move
        board[x_endSpace][y_endSpace] = board[x_startSpace][y_startSpace];
        board[x_startSpace][y_startSpace] = nullptr;
    }


    // Updating king position
    if(p->type == "king") {
        if(player == "white") {
            whiteKingPos = endCoords;
            // Check to see if white king castled, if so then rook needs to be moved
            if(x_startSpace == 4 && y_startSpace == 0) {
                if(x_endSpace == 6 && y_endSpace == 0) {
                    board[5][0] = board[7][0];
                    board[7][0] = nullptr;
                }
                else if(x_endSpace == 2 && y_endSpace == 0) {
                    board[3][0] = board[0][0];
                    board[0][0] = nullptr;
                }
            }
        }
        else {
            blackKingPos = endCoords;
            // Check to see if black king castled, if so then rook needs to be moved
            if(x_startSpace == 4 && y_startSpace == 7) {
                if(x_endSpace == 6 && y_endSpace == 7) {
                    board[5][7] = board[7][7];
                    board[7][7] = nullptr;
                }
                else if(x_endSpace == 2 && y_endSpace == 7) {
                    board[3][7] = board[0][7];
                    board[0][7] = nullptr;                   
                }
            }
        }
    }

    bool doubleMove = false;
    bool wasPromoted = false;
    bool valid = false;
    std::string promotion;
    // Check to see if pawn has reached the last row or just double moved
    if(p->type == "pawn") {
        if(p->color == "white") {
            if(y_endSpace == 7) {
                wasPromoted = true;
            }
            if(y_startSpace == 1 && y_endSpace == 3) {
                p->justDoubleMoved = true;
                doubleMove = true;
            }
        }
        else {
            if(y_endSpace == 0) {
                wasPromoted = true;
            }
            if(y_startSpace == 6 && y_endSpace == 4) {
                p->justDoubleMoved = true;
                doubleMove = true;
            }
        }
    }

    // Update the justDoubleMoved value for each piece
    // This is needed for determining if an en passant is legal
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] !=nullptr) {
                if(i != x_endSpace && j != y_endSpace) {
                    board[i][j]->justDoubleMoved = false;
                }
                else {
                    if(!doubleMove) {
                        board[i][j]->justDoubleMoved = false;
                    }
                }
            }
        }
    }

    // Pawn promotion
    if(wasPromoted) {
        do {
            if(!aiTurn) {
                std::cout << "Choose the pawn's promotion: ";
                std::cin >> promotion;
            }
            else {
                promotion = "queen";
            }
            for(int i = 0; i < promotion.length(); i++) {
                promotion[i] = tolower(promotion[i]);
            }
            valid = validPromotion(promotion);
            if(!valid) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        while(!valid);

        Piece* promotedPiece = new Piece(p->color, promotion);
        board[x_endSpace][y_endSpace] = promotedPiece;
    }

    // Update board and valid moves
    calculateBoardState(player);

    p->hasMoved = true;
    if(wasPromoted) {
        delete p;
    }
    delete temp;

    return true;
}

// Function that recalculates the valid moves for each piece
// and checks to see if there is a checkmate, stalemenate, etc.
// Called after every move
// Player is the color of the piece that just moved, needed for determining if there is a stalemate
void Chessboard::calculateBoardState(std::string player) {
    whiteValidMoves.clear();
    blackValidMoves.clear();
    calculatePossibleMoves();
    calculateKingStates(player);
}

// Function that calculates the possible moves for each piece
// Called at the start of the match and after each move by calculateBoardState
void Chessboard::calculatePossibleMoves() {
    whitePossibleMoves.clear();
    blackPossibleMoves.clear();
    Piece* p;
    std::pair<int,int> startCoords;
    std::pair<int,int> endCoords;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr) {
                p = board[i][j];
                startCoords = std::make_pair(i,j);
                if(p->type == "pawn") {
                    if(p->color == "white") {
                        if(j+1 < 8 && board[i][j+1] == nullptr) {
                            endCoords = std::make_pair(i,j+1);
                            whitePossibleMoves[std::make_pair(startCoords, endCoords)] = 1;
                        }
                        if(j == 1 && board[i][j+1] == nullptr && board[i][j+2] == nullptr) {
                            endCoords = std::make_pair(i,j+2);
                            whitePossibleMoves[std::make_pair(startCoords, endCoords)] = 1;
                        }
                        if(j+1 < 8 && i+1 < 8 && board[i+1][j+1] != nullptr && board[i+1][j+1]->color == "black") {
                            endCoords = std::make_pair(i+1,j+1);
                            whitePossibleMoves[std::make_pair(startCoords, endCoords)] = 1;                      
                        }
                        if(j+1 < 8 && i-1 >= 0 && board[i-1][j+1] != nullptr && board[i-1][j+1]->color == "black") {
                            endCoords = std::make_pair(i-1,j+1);
                            whitePossibleMoves[std::make_pair(startCoords, endCoords)] = 1;                               
                        }
                        // En Passant
                        if(j == 4 && i+1 < 8 && board[i+1][j] != nullptr && board[i+1][j]->type == "pawn" && board[i+1][j]->color == "black") {
                            if(board[i+1][j]->justDoubleMoved) {
                                endCoords = std::make_pair(i+1,j+1);
                                whitePossibleMoves[std::make_pair(startCoords, endCoords)] = 1;     
                            }
                        }
                        if(j == 4 && i-1 >= 0 && board[i-1][j] != nullptr && board[i-1][j]->type == "pawn" && board[i-1][j]->color == "black") {
                            if(board[i-1][j]->justDoubleMoved) {
                                endCoords = std::make_pair(i-1,j+1);
                                whitePossibleMoves[std::make_pair(startCoords, endCoords)] = 1;  
                            }
                        }
                    }
                    else {
                        if(j-1 >= 0 && board[i][j-1] == nullptr) {
                            endCoords = std::make_pair(i,j-1);
                            blackPossibleMoves[std::make_pair(startCoords, endCoords)] = 1;
                        }
                        if(j == 6 && board[i][j-1] == nullptr && board[i][j-2] == nullptr) {
                            endCoords = std::make_pair(i,j-2);
                            blackPossibleMoves[std::make_pair(startCoords, endCoords)] = 1;
                        }
                        if(j-1 >= 0 && i+1 < 8 && board[i+1][j-1] != nullptr && board[i+1][j-1]->color == "white") {
                            endCoords = std::make_pair(i+1,j-1);
                            blackPossibleMoves[std::make_pair(startCoords, endCoords)] = 1;                        
                        }
                        if(j-1 >= 0 && i-1 >= 0 && board[i-1][j-1] != nullptr && board[i-1][j-1]->color == "white") {
                            endCoords = std::make_pair(i-1,j-1);
                            blackPossibleMoves[std::make_pair(startCoords, endCoords)] = 1;                          
                        }
                        // En Passant
                        if(j == 3 && i+1 < 8 && board[i+1][j] != nullptr && board[i+1][j]->type == "pawn" && board[i+1][j]->color == "white") {
                            if(board[i+1][j]->justDoubleMoved) {
                                endCoords = std::make_pair(i+1,j-1);
                                blackPossibleMoves[std::make_pair(startCoords, endCoords)] = 1; 
                            }
                        }
                        if(j == 3 && i-1 >= 0 && board[i-1][j] != nullptr && board[i-1][j]->type == "pawn" && board[i-1][j]->color == "white") {
                            if(board[i-1][j]->justDoubleMoved) {
                                endCoords = std::make_pair(i-1,j-1);
                                blackPossibleMoves[std::make_pair(startCoords, endCoords)] = 1;  
                            }
                        }
                    }
                }
                else if(p->type == "rook") {
                    // Vertical movement
                    int y = j+1;
                    while(y < 8 && board[i][y] == nullptr) {
                        possibleMove(p,startCoords,i,y);
                        y++;
                    }
                    if(y < 8) {
                        possibleMove(p,startCoords,i,y);
                    }
                    y = j-1;
                    while(y >= 0 && board[i][y] == nullptr) {
                        possibleMove(p,startCoords,i,y);
                        y--;
                    }
                    if(y >= 0) {
                        possibleMove(p,startCoords,i,y);
                    }
                    // Horizontal movement
                    int x = i+1;
                    while(x < 8 && board[x][j] == nullptr) {
                        possibleMove(p,startCoords,x,j);
                        x++;
                    }
                    if(x < 8) {
                        possibleMove(p,startCoords,x,j);
                    }
                    x = i-1;
                    while(x >= 0 && board[x][j] == nullptr) {
                        possibleMove(p,startCoords,x,j);
                        x--;
                    }
                    if(x >= 0) {
                        possibleMove(p,startCoords,x,j);
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
                            possibleMove(p,startCoords,x,y);
                        }
                    }
                }
                else if(p->type == "bishop") {
                    // 45 degree angle movement
                    int x = i+1;
                    int y = j+1;
                    while(x < 8 && y < 8 && board[x][y] == nullptr) {
                        possibleMove(p,startCoords,x,y);
                        x++;
                        y++;
                    }
                    if(x < 8 && y < 8) {
                        possibleMove(p,startCoords,x,y);
                    }
                    x = i-1;
                    y = j-1;
                    while(x >= 0 && y >= 0 && board[x][y] == nullptr) {
                        possibleMove(p,startCoords,x,y);
                        x--;
                        y--;
                    }
                    if(x >= 0 && y >= 0) {
                        possibleMove(p,startCoords,x,y);
                    }
                    // 135 degree angle movment
                    x = i+1;
                    y = j-1;
                    while(x < 8 && y >= 0 && board[x][y] == nullptr) {
                        possibleMove(p,startCoords,x,y);
                        x++;
                        y--;
                    }
                    if(x < 8 && y >= 0) {
                        possibleMove(p,startCoords,x,y);
                    }
                    x = i-1;
                    y = j+1;
                    while(x >= 0 && y < 8 && board[x][y] == nullptr) {
                        possibleMove(p,startCoords,x,y);
                        x--;
                        y++;
                    }
                    if(x >= 0 && y < 8) {
                        possibleMove(p,startCoords,x,y);
                    }
                }
                else if(p->type == "queen") {
                    // Vertical movement
                    int y = j+1;
                    while(y < 8 && board[i][y] == nullptr) {
                        possibleMove(p,startCoords,i,y);
                        y++;
                    }
                    if(y < 8) {
                        possibleMove(p,startCoords,i,y);
                    }
                    y = j-1;
                    while(y >= 0 && board[i][y] == nullptr) {
                        possibleMove(p,startCoords,i,y);
                        y--;
                    }
                    if(y >= 0) {
                        possibleMove(p,startCoords,i,y);
                    }
                    // Horizontal movement
                    int x = i+1;
                    while(x < 8 && board[x][j] == nullptr) {
                        possibleMove(p,startCoords,x,j);
                        x++;
                    }
                    if(x < 8) {
                        possibleMove(p,startCoords,x,j);
                    }

                    x = i-1;
                    while(x >= 0 && board[x][j] == nullptr) {
                        possibleMove(p,startCoords,x,j);
                        x--;
                    }
                    if(x >= 0) {
                        possibleMove(p,startCoords,x,j);
                    }
                    // 45 degree angle movement
                    x = i+1;
                    y = j+1;
                    while(x < 8 && y < 8 && board[x][y] == nullptr) {
                        possibleMove(p,startCoords,x,y);
                        x++;
                        y++;
                    }
                    if(x < 8 && y < 8) {
                        possibleMove(p,startCoords,x,y);
                    }
                    x = i-1;
                    y = j-1;
                    while(x >= 0 && y >= 0 && board[x][y] == nullptr) {
                        possibleMove(p,startCoords,x,y);
                        x--;
                        y--;
                    }
                    if(x >= 0 && y >= 0) {
                        possibleMove(p,startCoords,x,y);
                    }
                    // 135 degree angle movment
                    x = i+1;
                    y = j-1;
                    while(x < 8 && y >= 0 && board[x][y] == nullptr) {
                        possibleMove(p,startCoords,x,y);
                        x++;
                        y--;
                    }
                    if(x < 8 && y >= 0) {
                        possibleMove(p,startCoords,x,y);
                    }
                    x = i-1;
                    y = j+1;
                    while(x >= 0 && y < 8 && board[x][y] == nullptr) {
                        possibleMove(p,startCoords,x,y);
                        x--;
                        y++;
                    }
                    if(x >= 0 && y < 8) {
                        possibleMove(p,startCoords,x,y);
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
                            possibleMove(p,startCoords,x,y);
                        }
                    }
                }
            }
        }
    }
    // Check to see if kings can castle
    Piece* p2;
    startCoords = std::make_pair(4,0);
    if(board[4][0] != nullptr) {
        p = board[4][0];
        if(p->type == "king" && p->color == "white" && !(p->hasMoved) && !isWhiteInCheck) {
            p2 = board[7][0];
            if(p2 != nullptr && p2->type == "rook" && p2->color == "white" && !(p2->hasMoved)) {
                if(board[5][0] == nullptr && board[6][0] == nullptr) {
                    if(!canBlackCapture(std::make_pair(5,0)) && !canBlackCapture(std::make_pair(6,0))) {
                        endCoords = std::make_pair(6,0);
                        whitePossibleMoves[std::make_pair(startCoords, endCoords)] = 1;  
                    }
                }
            }

            p2 = board[0][0];
            if(p2 != nullptr && p2->type == "rook" && p2->color == "white" && !(p2->hasMoved)) {
                if(board[3][0] == nullptr && board[2][0] == nullptr && board[1][0] == nullptr) {
                    if(!canBlackCapture(std::make_pair(3,0)) && !canBlackCapture(std::make_pair(2,0))) {
                        endCoords = std::make_pair(2,0);
                        whitePossibleMoves[std::make_pair(startCoords, endCoords)] = 1;  
                    }
                }
            }
        }
    }
    startCoords = std::make_pair(4,7);
    if(board[4][7] != nullptr) {
        p = board[4][7];
        if(p->type == "king" && p->color == "black" && !(p->hasMoved) && !isBlackInCheck) {
            p2 = board[7][7];
            if(p2 != nullptr && p2->type == "rook" && p2->color == "black" && !(p2->hasMoved)) {
                if(board[5][7] == nullptr && board[6][7] == nullptr) {
                    if(!canWhiteCapture(std::make_pair(5,7)) && !canWhiteCapture(std::make_pair(6,7))) {
                        endCoords = std::make_pair(6,7);
                        blackPossibleMoves[std::make_pair(startCoords, endCoords)] = 1;  
                    }
                }
            }

            p2 = board[0][7];
            if(p2 != nullptr && p2->type == "rook" && p2->color == "black" && !(p2->hasMoved)) {
                if(board[3][7] == nullptr && board[2][7] == nullptr) {
                    if(!canWhiteCapture(std::make_pair(3,7)) && !canWhiteCapture(std::make_pair(2,7))) {
                        endCoords = std::make_pair(2,7);
                        blackPossibleMoves[std::make_pair(startCoords, endCoords)] = 1;  
                    }
                }
            }
        }
    }

    return;
}

// Checks to see if the kings are in check, checkmate, or if there is a stalemate
// Also checks each possible move to see if the move is valid, meaning it does not put the player's king in check
void Chessboard::calculateKingStates(std::string player) {
    if(canWhiteCapture(blackKingPos)) {
        isBlackInCheck = true;
    }
    else {
        isBlackInCheck = false;
    }
    if(canBlackCapture(whiteKingPos)) {
        isWhiteInCheck = true;
    }
    else {
        isWhiteInCheck = false;
    }
    // Check each possible move to see if it places the player's king in check
    Piece* p;
    Piece* temp;
    int x_startSpace, y_startSpace;
    int x_endSpace, y_endSpace;
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> tempWhitePossibleMoves = whitePossibleMoves;
    std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> tempBlackPossibleMoves = blackPossibleMoves;

    // Check possible moves for white
    for(std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int>::iterator it = tempWhitePossibleMoves.begin(); it != tempWhitePossibleMoves.end(); it++) {
        x_startSpace = it->first.first.first;
        y_startSpace = it->first.first.second;
        x_endSpace = it->first.second.first;
        y_endSpace = it->first.second.second;

        p = board[x_startSpace][y_startSpace];
        temp = board[x_endSpace][y_endSpace];

        board[x_endSpace][y_endSpace] = board[x_startSpace][y_startSpace];
        board[x_startSpace][y_startSpace] = nullptr;
        if(p->type == "king") {
            whiteKingPos = std::make_pair(x_endSpace, y_endSpace);
        }

        calculatePossibleMoves();

        if(!canBlackCapture(whiteKingPos)) {
            whiteValidMoves[it->first] = 1;
        }

        board[x_endSpace][y_endSpace] = temp;
        board[x_startSpace][y_startSpace] = p;
        if(p->type == "king") {
            whiteKingPos = std::make_pair(x_startSpace, y_startSpace);
        }
    }

    // Check possible moves for black
    for(std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int>::iterator it = tempBlackPossibleMoves.begin(); it != tempBlackPossibleMoves.end(); it++) {
        x_startSpace = it->first.first.first;
        y_startSpace = it->first.first.second;
        x_endSpace = it->first.second.first;
        y_endSpace = it->first.second.second;

        p = board[x_startSpace][y_startSpace];
        temp = board[x_endSpace][y_endSpace];

        board[x_endSpace][y_endSpace] = board[x_startSpace][y_startSpace];
        board[x_startSpace][y_startSpace] = nullptr;
        if(p->type == "king") {
            blackKingPos = std::make_pair(x_endSpace, y_endSpace);
        }


        calculatePossibleMoves();

        if(!canWhiteCapture(blackKingPos)) {
            blackValidMoves[it->first] = 1;
        }

        board[x_endSpace][y_endSpace] = temp;
        board[x_startSpace][y_startSpace] = p;
        if(p->type == "king") {
            blackKingPos = std::make_pair(x_startSpace, y_startSpace);
        }
    }

    whitePossibleMoves = tempWhitePossibleMoves;
    blackPossibleMoves = tempBlackPossibleMoves;

    // Check for checkmates and stalemate
    if(isWhiteInCheck) {
        if(whiteValidMoves.size() > 0) {
            isWhiteInCheckmate = false;
        }
        else {
            isWhiteInCheckmate = true;
        }
    }
    if(isBlackInCheck) {
        if(blackValidMoves.size() > 0) {
            isBlackInCheckmate = false;
        }
        else {
            isBlackInCheckmate = true;
        }
    }

    if(player == "white") {
        if(blackValidMoves.size() == 0) {
            isStalemate = true;
        }
        else {
            isStalemate = false;
        }
    }
    else {
        if(whiteValidMoves.size() == 0) {
            isStalemate = true;
        }
        else {
            isStalemate = false;
        }
    }
}

// Returns the piece at coordinates x and y
Piece* const Chessboard::getPieceAt(int x, int y) {
    return board[x][y];
}

// Getter for isWhiteInCheck
bool const Chessboard::getIsWhiteInCheck() {
    return isWhiteInCheck;
}

// Getter for isBlackInCheck
bool const Chessboard::getIsBlackInCheck() {
    return isBlackInCheck;
}

// Getter for isWhiteInCheckmate
bool const Chessboard::getIsWhiteInCheckmate() {
    return isWhiteInCheckmate;
}

// Getter for isBlackInCheckmate
bool const Chessboard::getIsBlackInCheckmate() {
    return isBlackInCheckmate;
}

// Getter for isStalemate
bool const Chessboard::getIsStalemate() {
    return isStalemate;
}

// Getter for whiteValidMoves
std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> const Chessboard::getWhiteValidMoves() {
    return whiteValidMoves;
}

// Getter for blackValidMoves
std::map<std::pair<std::pair<int,int>, std::pair <int,int>>, int> const Chessboard::getBlackValidMoves() {
    return blackValidMoves;
}

// Adds a piece to the board at the specified xcord and ycord
// Type specifies which type of piece to add
// Color specifies the color of the piece being added
void Chessboard::addPiece(std::string color, std::string type, int xcord, int ycord) {
    Piece* p = new Piece(color, type);
    board[xcord][ycord] = p;
}

// Sees if a move is possible and, if so, adds it to the possibleMoves map
void Chessboard::possibleMove(Piece* p, std::pair<int,int> startCoords, int x, int y) {
    std::pair<int,int> endCoords = std::make_pair(x,y);
    if(board[x][y] == nullptr || board[x][y]->color != p->color) {
        if(p->color == "white") {
            whitePossibleMoves[std::make_pair(startCoords,endCoords)] = 1;
        }
        else {
            blackPossibleMoves[std::make_pair(startCoords,endCoords)] = 1;
        }
    }
}

// Checks to see if black can attack the space x, y with some piece
bool Chessboard::canBlackCapture(std::pair<int,int> endCoords) {
    std::pair<int,int> startCoords;
    std::pair<std::pair<int,int>, std::pair <int,int>> move;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr && board[i][j]->color == "black") {
                startCoords = std::make_pair(i,j);
                move = std::make_pair(startCoords, endCoords);
                if(blackPossibleMoves.find(move) != blackPossibleMoves.end()) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Checks to see if white can attack the space x, y with some piece
bool Chessboard::canWhiteCapture(std::pair<int,int> endCoords) {
    std::pair<int,int> startCoords;
    std::pair<std::pair<int,int>, std::pair <int,int>> move;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr && board[i][j]->color == "white") {
                startCoords = std::make_pair(i,j);
                move = std::make_pair(startCoords, endCoords);
                if(whitePossibleMoves.find(move) != whitePossibleMoves.end()) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Checks to see if the user inputted promotion is valid
bool Chessboard::validPromotion(std::string promotion) {
    if(promotion == "rook") {
        return true;
    }
    else if(promotion == "bishop") {
        return true;
    }
    else if(promotion == "knight") {
        return true;
    }
    else if(promotion == "queen") {
        return true;
    }
    else {
        std::cout << "Invalid promotion: that is not a valid promotion" << std::endl;
        return false;
    }
}

// Clears the board
void Chessboard::deleteBoard() {
    Piece *temp;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j] != nullptr) {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
    }
}