#pragma once
#include "Spot.hpp"
#include <iostream>

using namespace std;

class Board{
public: 
    vector<vector<Spot*>> board;
    Board();
    Spot* getSpot(int x,int y); 
    void resetBoard();
    void displayBoard();
    Spot* getSpot(string pos);
};