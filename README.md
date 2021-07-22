# Chess_gregbaroni

## Chess

A project coded in C++ that allows you to play chess against another person or against an AI.

## How to Compile

If you are using a Mac or Linux you should be able to download the repository and compile the executable by typing "make chess" without quotations at the command line. By default, the makefile will use g++ to compile, but you can change this to gcc by changing CXX to gcc.

If you are using windows you will need to manually compile the files chessboard.cpp, chessAI.cpp, and main.cpp into an executable.

## How to Play

Once you start the program, you will be asked whether you want to play a two player game or against AI. Type either "2p" or "AI" without quotations and press enter to continue.

If you choose AI, you will then be asked whether you want to play as white or black. Type either "white" or "black" without quoations and press enter to continue.

Once the game starts, you will be presented with a board like this:



The letters on the board indicate the different pieces.
- p / P = pawn
- r / R = rook
- n / N = knight
- b / B = bishop
- q / Q = queen
- k / K = king

The lowercase letters represent the white pieces and the uppercase letters represent the black pieces.

To perform a move, type the start coordinate followed by the end coordinate.
So, to move the pawn at e2 up two spaces, you would type "e2 e4" without quotations and press enter.
