#ifndef Duck_hpp
#define Duck_hpp

#include "QuackBehavior.hpp"
#include "FlyBehavior.hpp"

#include <memory>
#include <iostream>

using namespace std;

class Duck{
    public:

        void swim(){ cout<<"All ducks float, even decoys! \n"; }
        virtual void display() const = 0;
        
        void performFly(){flyBehavior->fly(); }
        void performQuack(){quackBehavior->quack(); }

        void setFlyBehavior(unique_ptr<FlyBehavior> fb){flyBehavior=std::move(fb); }
        void setQuackBehavior(unique_ptr<QuackBehavior> qb){quackBehavior=std::move(qb); }
        // ~Duck()=default;
        virtual ~Duck() = default;

    protected:
        unique_ptr<FlyBehavior> flyBehavior = NULL;
        unique_ptr<QuackBehavior> quackBehavior = NULL;

};
#endif