#include "Bishop.hpp"
#include "../Spot.hpp"
#include "../Board.hpp"

Bishop::Bishop(bool colour): Piece(colour) {}

bool Bishop::canMove(Board *board, Spot *start, Spot *end){
    return true;
    int xMove = abs(start->getX() - end->getX());
    int yMove = abs(start->getY() - end->getY());

    // Bishops move diagonally, so the absolute difference in x and y must be the same
    if (xMove != yMove) return false;

    // Check if the path is clear
    int xDirection = (end->getX() - start->getX()) > 0 ? 1 : -1;
    int yDirection = (end->getY() - start->getY()) > 0 ? 1 : -1;

    int x = start->getX() + xDirection;
    int y = start->getY() + yDirection;

    while (x != end->getX() && y != end->getY()) {
        if (board->getSpot(x, y)->getPiece() != nullptr) return false;
        x += xDirection;
        y += yDirection;
    }

    // Ensure the destination spot is either empty or occupied by an opponent's piece
    return end->getPiece() == nullptr || end->getPiece()->getColour() != this->getColour();
}

string Bishop::getSymbol(){ return "Bishop"; }

void Bishop::move(Board *board, Spot *start, Spot *end) {
    if (!canMove(board, start, end)) {
        throw invalid_argument("Invalid move for Bishop");
    }
    this->setMoved(true);

    // Capture the piece on the destination spot, if any
    if (end->getPiece() != nullptr) delete end->getPiece();

    // Move the Bishop to the destination spot
    end->setPiece(this);
    start->setPiece(nullptr);
}
