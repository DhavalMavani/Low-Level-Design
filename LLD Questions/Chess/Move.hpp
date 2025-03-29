#pragma once

#include <iostream>
#include "Game.hpp" // Include Game.hpp to resolve incomplete type issues

using namespace std;

class Move{
public:
    Spot* strPos;
    Spot* endPos;
    Player* player;
    Piece* strPiece;
    Piece* endPiece;

    Move(Spot* strPos,Spot* endPos,Player* player){
        this->strPos=strPos;
        this->endPos=endPos;
        this->player=player;
        this->strPiece=strPos->getPiece();
        this->endPiece=endPos->getPiece();
    }

};