#ifndef Fly_Behavior_hpp
#define Fly_Behavior_hpp

class FlyBehavior{
    public:
        virtual ~FlyBehavior() = default;
		virtual void fly() = 0;
};

#endif