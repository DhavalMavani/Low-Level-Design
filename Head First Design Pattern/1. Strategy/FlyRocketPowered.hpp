#ifndef FLY_ROCKET_POWERED_hpp
#define FLY_ROCKET_POWERED_hpp

#include "FlyBehavior.hpp"
#include <iostream>
using namespace std;
class FlyRocketPowered : public FlyBehavior {
	public:
		void fly() { cout << "I'm flying with a rocket!\n"; }
};

#endif