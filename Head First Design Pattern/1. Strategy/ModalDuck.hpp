#ifndef Modal_Duck_hpp
#define Modal_Duck_hpp

#include "Duck.hpp"
#include "FlyNoWay.hpp"
#include "Quack.hpp"

#include <iostream>
using namespace std;

class ModalDuck: public Duck{
    public:
        ModalDuck(){
            setFlyBehavior(make_unique<FlyNoWay> ());
            setQuackBehavior(make_unique <Quack> () );
        }
        ~ModalDuck()=default;
        void display() const override{ cout<<" I'm a Modal Duck \n"; }

};
#endif