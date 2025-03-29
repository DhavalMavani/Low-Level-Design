#pragma once

#include <iostream>
using namespace std;

class Board;
class Spot;

class Piece{
private:
    bool colour;
    bool killed;
    bool moved;
public: 
    Piece(bool colour);
    bool getColour();
    void setColour(bool colour);
    bool isKilled();
    void setKilled(bool killed);
    bool hasMoved();
    void setMoved(bool moved);

    virtual bool canMove(Board* board, Spot* start, Spot* end) = 0;
    virtual string getSymbol() = 0;
    virtual void move(Board* board, Spot* start, Spot* end) = 0;
};