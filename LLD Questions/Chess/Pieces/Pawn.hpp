#pragma once
#include "Piece.hpp"

class Pawn: public Piece{
public:
    Pawn(bool colour);
    bool canMove(Board* board, Spot* start, Spot* end) override;
    virtual string getSymbol() override;
    virtual void move(Board* board, Spot* start, Spot* end) override;
    void promote(Board* board, Spot* end);
};