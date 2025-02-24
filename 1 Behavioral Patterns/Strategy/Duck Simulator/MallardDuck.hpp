#ifndef Mallard_Duck_hpp
#define Mallard_Duck_hpp

#include "Duck.hpp"
#include "FlyWithWings.hpp"
#include "Quack.hpp"

#include <memory> 
#include <iostream>
// using namespace std;

class MallardDuck: public Duck{
    public:
        MallardDuck(){
            setFlyBehavior(std::make_unique<FlyWithWings>());
            setQuackBehavior(std::make_unique <Quack> () );
        }
        ~MallardDuck()=default;
        void display() const override{ std::cout<<" I'm a real Mallard Duck \n"; }

};
#endif