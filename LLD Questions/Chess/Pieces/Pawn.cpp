#include "Pawn.hpp"
#include "../Spot.hpp"
#include "../Board.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Queen.hpp"
#include "Bishop.hpp"

Pawn::Pawn(bool colour): Piece(colour) {}

bool Pawn::canMove(Board *board, Spot *start, Spot *end){
    return true;
    // Pawns cannot move to a spot occupied by a piece of the same color
    if (end->getPiece() != nullptr && end->getPiece()->getColour() == this->getColour()) {
        return false;
    }

    int x = abs(start->getX() - end->getX());
    int y = abs(start->getY() - end->getY());

    // Pawns move forward only (white moves up, black moves down)
    if (this->getColour()) {
        if (end->getY() >= start->getY()) { return false; }
    } else {
        if (end->getY() <= start->getY()) { return false; }
    }

    // Standard move: one step forward
    if (y == 1 && x == 0 && end->getPiece() == nullptr) {
        return true;
    }

    // Initial move: two steps forward
    if (y == 2 && x == 0 && end->getPiece() == nullptr && !this->hasMoved()) {
        return true;
    }

    // Capture move: one step diagonally forward
    if (y == 1 && x == 1 && end->getPiece() != nullptr) {
        return true;
    }

    return false;
}

string Pawn::getSymbol(){ return "Pawn"; }

void Pawn::move(Board *board, Spot *start, Spot *end) {
    // Perform the move
    end->setPiece(this);
    start->setPiece(nullptr);

    // Mark the pawn as having moved
    this->setMoved(true);

    // Handle promotion (if the pawn reaches the last rank)
    if ((this->getColour() && end->getY() == 7) || (!this->getColour() && end->getY() == 0)) {
        // Promote the pawn to a queen (or other piece, depending on the rules)
        // For simplicity, we'll assume promotion to a queen
        promote(board, end );
    }
}

void Pawn::promote(Board *board, Spot *end){
    char choice;
    std::cout << "Promote pawn to (Q)ueen, (R)ook, (B)ishop, or (K)night: ";
    std::cin >> choice;

    Piece *newPiece = nullptr;
    switch (toupper(choice)) {
        case 'Q':
            newPiece = new Queen(this->getColour());
            break;
        case 'R':
            newPiece = new Rook(this->getColour());
            break;
        case 'B':
            newPiece = new Bishop(this->getColour());
            break;
        case 'K':
            newPiece = new Knight(this->getColour());
            break;
        default:
            std::cout << "Invalid choice. Defaulting to Queen." << std::endl;
            newPiece = new Queen(this->getColour());
            break;
    }
    end->setPiece(newPiece);
    delete this; // Remove the pawn from memory
}
