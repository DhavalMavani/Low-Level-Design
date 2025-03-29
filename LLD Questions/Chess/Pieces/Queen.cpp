#include "Queen.hpp"
#include "../Spot.hpp"
#include "../Board.hpp"

Queen::Queen(bool colour): Piece(colour) {}

bool Queen::canMove(Board *board, Spot *start, Spot *end){
    return true;
    // Check if the end spot has a piece of the same color
    if (end->getPiece() != nullptr && end->getPiece()->getColour() == this->getColour()) {
        return false;
    }

    int x = abs(start->getX() - end->getX());
    int y = abs(start->getY() - end->getY());

    // A queen can move like a rook or a bishop
    if (x == y || x == 0 || y == 0) {
        // Check if the path is clear
        int xDirection = (end->getX() - start->getX()) == 0 ? 0 : (end->getX() - start->getX()) / abs(end->getX() - start->getX());
        int yDirection = (end->getY() - start->getY()) == 0 ? 0 : (end->getY() - start->getY()) / abs(end->getY() - start->getY());

        int currentX = start->getX() + xDirection;
        int currentY = start->getY() + yDirection;

        while (currentX != end->getX() || currentY != end->getY()) {
            if (board->getSpot(currentX, currentY)->getPiece() != nullptr) {
                return false;
            }
            currentX += xDirection;
            currentY += yDirection;
        }
        return true;
    }

    return false;
}

string Queen::getSymbol(){ return "Queen"; }

void Queen::move(Board *board, Spot *start, Spot *end) {
    if (!canMove(board, start, end)) {
        throw invalid_argument("Invalid move for Queen");
    }

    this->setMoved(true);
    
    // Capture the piece on the destination spot, if any
    if (end->getPiece() != nullptr) delete end->getPiece();

    // Move the Queen to the destination spot
    end->setPiece(this);
    start->setPiece(nullptr);
}
