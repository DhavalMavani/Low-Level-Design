#ifndef Quack_Behavior_hpp
#define Quack_Behavior_hpp

class QuackBehavior{
    public:
    virtual void quack()=0;
    virtual ~QuackBehavior() = default;
};

#endif