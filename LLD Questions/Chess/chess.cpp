// g++ *.cpp Pieces/*.cpp -o chess   

#include <iostream>

#include "Board.hpp"
#include "Game.hpp"
#include "Player.hpp"

using namespace std;

int main(){
    Player* p1=new Player("Dhaval",true);
    Player* p2=new Player("Tay",false);

    Game* g1= new Game(p1, p2);
    return 0;
}