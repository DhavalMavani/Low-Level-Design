#include "Piece.hpp"

Piece::Piece(bool colour) :colour(colour) {
    killed=false;
    moved=false;
}

bool Piece::getColour() { return colour; }

void Piece::setColour(bool colour){this->colour=colour;}

bool Piece::isKilled() { return killed; }

void Piece::setKilled(bool killed){ this->killed= killed; }

bool Piece::hasMoved(){ return moved; }

void Piece::setMoved(bool moved){ this->moved=moved;}
