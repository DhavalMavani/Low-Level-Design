#ifndef Mute_Duck_hpp
#define Mute_Duck_hpp

#include "Duck.hpp"
#include "FlyWithWings.hpp"
#include "MuteQuack.hpp"
#include <iostream>
#include <memory>

using namespace std;

class MuteDuck : public Duck {
	public:
		MuteDuck(){
            flyBehavior = make_unique<FlyWithWings>();
            quackBehavior = make_unique<MuteQuack>();
        };
		void display() const override { cout << "I am a mute duck \n"; }
};

#endif