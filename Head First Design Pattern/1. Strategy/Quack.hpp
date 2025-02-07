#ifndef Quack_hpp
#define Quack_hpp

#include "QuackBehavior.hpp"
#include <iostream>

using namespace std;

class Quack: public QuackBehavior{
    public: 
        void quack() override{ cout<<"I can quack !! \n"; }
};
#endif