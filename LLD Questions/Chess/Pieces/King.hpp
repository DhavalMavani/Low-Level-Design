#pragma once
#include "Piece.hpp"

class King: public Piece{
public:
    King(bool colour);
    bool canMove(Board* board, Spot* start, Spot* end) override;
    virtual string getSymbol() override;
    virtual void move(Board* board, Spot* start, Spot* end) override;
};