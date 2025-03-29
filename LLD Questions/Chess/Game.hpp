#pragma once

#include "Board.hpp"
#include "Player.hpp"
#include "Move.hpp"
#include "Enums.hpp"

#include <iostream>
#include <bits/stdc++.h>

using namespace std;

class Game{
public:
    pair<Player*,Player*> players;
    Board* board;
    vector<Move*> movesPlayed;
    Player* currPlayer;
    GAME_STATUS status;

    Game(Player* p1,Player* p2 );
    void initialise();

    void processMove(string strPos, string endPos);
    Board* getBoard();
    void switchTurn();
    void unDo();
};
