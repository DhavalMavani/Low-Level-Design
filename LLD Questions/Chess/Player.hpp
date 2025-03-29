#pragma once

#include <iostream>
using namespace std;

class Game; 

class Player {
public:
    string name;
    bool humanPlayer, isWhite;
    Game* currGame;
    Player(string name, bool isWhite) : name(name), isWhite(isWhite) {}
    void setCurrGame(Game* game) { this->currGame=game; }
    Game* getGame() { return this->currGame; }
    string getName(){ return name; }
    bool isWhiteSide() { return isWhite; }
    bool isHumanPlayer() { return humanPlayer; }
};