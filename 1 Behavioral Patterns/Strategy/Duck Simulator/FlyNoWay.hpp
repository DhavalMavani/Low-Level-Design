#ifndef Fly_No_Way_hpp
#define Fly_No_Way_hpp

#include "FlyBehavior.hpp"
#include <iostream>

using namespace std;

class FlyNoWay: public FlyBehavior {
    public:
        void fly() override{ cout<<"I can't Fly !! \n "; }
};

#endif