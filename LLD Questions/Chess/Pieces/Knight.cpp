#include "Knight.hpp"
#include "../Spot.hpp"
#include "../Board.hpp"

Knight::Knight(bool colour): Piece(colour) {}

bool Knight::canMove(Board *board, Spot *start, Spot *end){
    return true;
    if (end->getPiece() != nullptr && end->getPiece()->getColour() == this->getColour()) {
        return false; // Cannot move to a spot occupied by a piece of the same color
    }

    int x = abs(start->getX() - end->getX());
    int y = abs(start->getY() - end->getY());

    // Check if the move is an "L" shape
    return (x == 2 && y == 1) || (x == 1 && y == 2);
}

string Knight::getSymbol(){ return "Knight"; }

void Knight::move(Board *board, Spot *start, Spot *end) {
    if (!canMove(board, start, end)) {
        throw invalid_argument("Invalid move for Knight");
    }

    this->setMoved(true);
    
    // Capture the piece on the destination spot, if any
    if (end->getPiece() != nullptr) delete end->getPiece();

    // Move the Knight to the destination spot
    end->setPiece(this);
    start->setPiece(nullptr);
}
