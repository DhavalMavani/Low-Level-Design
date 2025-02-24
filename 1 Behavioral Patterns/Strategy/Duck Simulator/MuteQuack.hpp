#ifndef Mute_Quack_hpp
#define Mute_Quack_hpp

#include "QuackBehavior.hpp"
#include <iostream>

using namespace std;

class MuteQuack: public QuackBehavior{
    public: 
        void quack() override{ cout<<"I can't quack !! \n"; }
};
#endif