#include "King.hpp"
#include "Rook.hpp"
#include "../Spot.hpp"
#include "../Board.hpp"

King::King(bool colour): Piece(colour) {}

bool King::canMove(Board *board, Spot *start, Spot *end) {
    return true;
    if (end->getPiece() != nullptr && end->getPiece()->getColour() == this->getColour()) {
        return false; // Cannot move to a spot occupied by a piece of the same color
    }

    int x = abs(start->getX() - end->getX());
    int y = abs(start->getY() - end->getY());

    // King can move only one square in any direction
    if ((x <= 1 && y <= 1) && (x + y > 0)) {
        return true;
    }

    // Handle castling
    if (!this->hasMoved() && y == 0 && x == 2) { // Castling involves moving two squares horizontally
        int direction = (end->getX() - start->getX()) > 0 ? 1 : -1; // Determine castling direction
        Spot *rookSpot = board->getSpot(direction > 0 ? 7 : 0, start->getY()); // Rook's initial position
        Piece *rook = rookSpot->getPiece();

        // Check if the rook exists, hasn't moved, and the path is clear
        if (rook != nullptr && !rook->hasMoved() && rook->getSymbol() == "Rook") {
            for (int i = start->getX() + direction; i != end->getX(); i += direction) {
                if (board->getSpot(i, start->getY())->getPiece() != nullptr) {
                    return false; // Path is not clear
                }
            }
            return true; // Castling is valid
        }
    }

    return false;
}

string King::getSymbol(){ return "King"; }

void King::move(Board *board, Spot *start, Spot *end) {
    // Perform the move
    Piece *capturedPiece = end->getPiece();
    end->setPiece(this);
    start->setPiece(nullptr);
    this->setMoved(true);

    // Handle castling
    int x = abs(start->getX() - end->getX());
    if (x == 2) { // Castling move
        int direction = (end->getX() - start->getX()) > 0 ? 1 : -1; // Determine castling direction
        Spot *rookStartSpot = board->getSpot(direction > 0 ? 7 : 0, start->getY());
        Spot *rookEndSpot = board->getSpot(start->getX() + direction, start->getY());
        Piece *rook = rookStartSpot->getPiece();

        // Move the rook to its new position
        rookEndSpot->setPiece(rook);
        rookStartSpot->setPiece(nullptr);
        rook->move(board, rookStartSpot, rookEndSpot); // Update rook's state
    }
}
