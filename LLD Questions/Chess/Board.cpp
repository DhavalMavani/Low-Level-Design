#include "Board.hpp"
#include "Pieces/Rook.hpp"
#include "Pieces/Knight.hpp"
#include "Pieces/Pawn.hpp"
#include "Pieces/Bishop.hpp"
#include "Pieces/Queen.hpp"
#include "Pieces/King.hpp"
#include <iomanip>

Board::Board(){
    board.resize(8, vector<Spot*>(8,NULL));
    this->resetBoard();
}

Spot* Board::getSpot(int x, int y) { return board[x][y]; }

void Board::resetBoard(){
    // Initialize white pieces
    board[0][0] = new Spot(0, 0, new Rook(true));
    board[0][1] = new Spot(0, 1, new Knight(true));
    board[0][2] = new Spot(0, 2, new Bishop(true));
    board[0][3] = new Spot(0, 3, new Queen(true));
    board[0][4] = new Spot(0, 4, new King(true));
    board[0][5] = new Spot(0, 5, new Bishop(true));
    board[0][6] = new Spot(0, 6, new Knight(true));
    board[0][7] = new Spot(0, 7, new Rook(true));

    for (int i = 0; i < 8; i++) board[1][i] = new Spot(1, i, new Pawn(true));


    // Initialize black pieces
    board[7][0] = new Spot(7, 0, new Rook(false));
    board[7][1] = new Spot(7, 1, new Knight(false));
    board[7][2] = new Spot(7, 2, new Bishop(false));
    board[7][3] = new Spot(7, 3, new Queen(false));
    board[7][4] = new Spot(7, 4, new King(false));
    board[7][5] = new Spot(7, 5, new Bishop(false));
    board[7][6] = new Spot(7, 6, new Knight(false));
    board[7][7] = new Spot(7, 7, new Rook(false));

    for (int i = 0; i < 8; i++) board[6][i] = new Spot(6, i, new Pawn(false));

    // Initialize remaining board without any piece
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = new Spot(i, j, NULL);
        }
    }
}

void Board::displayBoard(){
    cout<<setw(12)<<"";
    for(char ch = 'a'; ch <= 'h'; ch++)
        cout<<setw(12)<<ch;
    cout<<endl;
    for (int i = 0; i < 8; i++) {
        cout<< setw(12) << 8-i;
        for (int j = 0; j < 8; j++) {
            Spot* spot = getSpot(i, j);
            if (spot->getPiece()) {
                string symbol = ""; 
                if (spot->getPiece()->getColour()) {
                    symbol = "W-" + spot->getPiece()->getSymbol();
                } else {
                    symbol = "B-" + spot->getPiece()->getSymbol();
                }
                cout << setw(12) <<symbol;
            } else {
                cout << setw(12) << ".";
            }
        }
        cout<< setw(12) << 8-i;
        cout << endl;
    }
    cout<<setw(12)<<"";
    for(char ch = 'a'; ch <= 'h'; ch++)
        cout<<setw(12)<<ch;
    cout<<endl;
    cout << endl;
}

Spot* Board::getSpot(string pos) {
    if (pos.length() != 2 || pos[0] < 'a' || pos[0] > 'h' || pos[1] < '1' || pos[1] > '8') {
        return nullptr; // Invalid input
    }

    int column = pos[0] - 'a'; // Convert column letter to index (0-7)
    int row = 8 - (pos[1] - '0'); // Convert row number to index (0-7)

    return board[row][column];
}
