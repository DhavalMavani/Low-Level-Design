#pragma once
#include "Pieces/Piece.hpp"

class Spot{
public:
    Spot(int x, int y,Piece* piece);
    int x,y;
    Piece* piece;

    int getX();
    int getY();
    Piece* getPiece();
    void setPiece(Piece* piece);
};