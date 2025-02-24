#ifndef Fly_With_Wings_hpp
#define Fly_With_Wings_hpp

#include "FlyBehavior.hpp"
#include <iostream>

using namespace std;

class FlyWithWings: public FlyBehavior {
    public:
        void fly() override{ cout<<"I'm flying!! \n "; }
};

#endif