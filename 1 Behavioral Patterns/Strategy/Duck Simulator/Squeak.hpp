#ifndef Squeak_hpp
#define Squeak_hpp

#include "QuackBehavior.hpp"
#include <iostream>

using namespace std;

class Squeak: public QuackBehavior{
    public: 
        void quack() override{ cout<<"I can squeak !! \n"; }
};
#endif