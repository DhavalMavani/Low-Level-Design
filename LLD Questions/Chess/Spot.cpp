#include "Spot.hpp"

Spot::Spot(int x, int y, Piece *piece){
    this->x=x;
    this->y=y;
    this->piece= piece;
}

int Spot::getX() { return x; }

int Spot::getY() { return y; }

Piece *Spot::getPiece() { return piece; }

void Spot::setPiece(Piece* piece){
    this->piece=piece;
}
