#pragma once
#include "Piece.hpp"

class Rook: public Piece{
public:

    Rook(bool colour);
    bool canMove(Board* board, Spot* start, Spot* end) override;
    virtual string getSymbol() override;
    virtual void move(Board* board, Spot* start, Spot* end) override;
};