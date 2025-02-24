#include <iostream>

using namespace std;

class IFooditem{
    public:
        virtual string getDescription()=0;
        virtual int getCost()=0;
};

class Pizza: public IFooditem{
    public:
        string getDescription() override { return "This is a pizza";};
        int getCost() override { return 200; }
};

class Burger: public IFooditem{
    public:
        string getDescription() override { return "This is a burger";};
        int getCost() override { return 100; }
};

class IExtraToppingsDecorator: public IFooditem{
    public:
        IFooditem* foodItem=NULL;
        IExtraToppingsDecorator(IFooditem* foodItem){ this->foodItem=foodItem; }
};


class ExtraCheeseDecorator: public IExtraToppingsDecorator{
    public:
        ExtraCheeseDecorator (IFooditem* foodItem) :  IExtraToppingsDecorator(foodItem) { }
        string getDescription() override{ return foodItem->getDescription() + " with extra Cheese"; }
        int getCost() override{return foodItem->getCost()+ 20 ; }
};

class ExtraSauceDecorator: public IExtraToppingsDecorator{
    public:
        ExtraSauceDecorator (IFooditem* foodItem) :  IExtraToppingsDecorator(foodItem) { }
        string getDescription() override{ return foodItem->getDescription() + " with sauce Cheese"; }
        int getCost() override{return foodItem->getCost()+ 10 ; }
};


int main(){
    IFooditem* pizzaOrder= new Pizza();                 // 200
    pizzaOrder= new ExtraCheeseDecorator(pizzaOrder);   // 20
    pizzaOrder= new ExtraCheeseDecorator(pizzaOrder);   // 20
    pizzaOrder= new ExtraSauceDecorator(pizzaOrder);    // 10
    cout<<pizzaOrder->getDescription()<<":  Amount = "<<pizzaOrder->getCost()<<" \n"; // 250
    
    IFooditem* burgerOrder= new Burger();                  // 100
    burgerOrder= new ExtraCheeseDecorator(burgerOrder);    // 20
    burgerOrder= new ExtraSauceDecorator(burgerOrder);     // 10
    cout<<burgerOrder->getDescription()<<":  Amount = "<<burgerOrder->getCost()<<" \n"; // 130

    return 0;
}
