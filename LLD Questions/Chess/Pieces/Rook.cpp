#include "Rook.hpp"

#include <iostream>
#include "../Spot.hpp"
#include "../Board.hpp"

using namespace std;

Rook::Rook(bool colour) : Piece(colour) { }

bool Rook::canMove(Board * board, Spot * start, Spot * end){ 
    return true;
    // Rook can move horizontally or vertically
    if (start->getX() == end->getX() || start->getY() == end->getY()) {
        // Check if the path between start and end is clear
        int xDirection = (end->getX() - start->getX()) == 0 ? 0 : (end->getX() - start->getX()) > 0 ? 1 : -1;
        int yDirection = (end->getY() - start->getY()) == 0 ? 0 : (end->getY() - start->getY()) > 0 ? 1 : -1;

        int x = start->getX() + xDirection;
        int y = start->getY() + yDirection;

        while (x != end->getX() || y != end->getY()) {
            if (board->getSpot(x, y)->getPiece() != nullptr) {
                return false;
            }
            x += xDirection;
            y += yDirection;
        }

        // Check if the end spot is either empty or has an opponent's piece
        if (end->getPiece() == nullptr || end->getPiece()->getColour() != start->getPiece()->getColour()) {
            return true;
        }
    }
    return false;
}

string Rook::getSymbol(){
    return "ROOK";
}

void Rook::move(Board* board, Spot* start, Spot* end){

    if (!canMove(board, start, end)) {
        throw invalid_argument("Invalid move for Rook");
    }
    
    this->setMoved(true);

    // Capture the piece at the end spot if it exists
    if (end->getPiece() != nullptr) delete end->getPiece();

    // Move the rook to the end spot
    end->setPiece(start->getPiece());
    start->setPiece(NULL);
    // cout << "Rook moved successfully!" << endl;
}
