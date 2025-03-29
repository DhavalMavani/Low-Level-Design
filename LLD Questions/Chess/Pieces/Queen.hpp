#pragma once
#include "Piece.hpp"

class Queen: public Piece{
public:
    Queen(bool colour);
    bool canMove(Board* board, Spot* start, Spot* end) override;
    virtual string getSymbol() override;
    virtual void move(Board* board, Spot* start, Spot* end) override;
};