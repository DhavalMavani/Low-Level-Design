#include <string>
#include <iostream>

using namespace std;

class Pizza{
    public:
        string name, dough, sauce;
        vector<string> toppings;

        virtual void prepare(){
            cout << "Preparing " << name<<" -> Tossing dough -> Adding sauce -> Adding toppings:  ";
            for(auto &topping : toppings) cout << topping << ", ";
            cout<<endl;
        }
        virtual void bake() const { cout << "Bake for 25 minutes at 350 \n"; }
        virtual void cut() { cout << "Cutting the pizza into diagonal slices\n"; }
        virtual void box() const { cout << "place pizza in offical PizzaStore box\n"; }

        void setName(string n) { name = n; }
        string getName() const {return name;}
};

class PizzaStore {
	public:
		Pizza* pizzaOrder(string type){
            Pizza* pizza = createPizza(type);
            pizza->prepare();
            pizza->bake();
            pizza->cut();
            pizza->box();
            return pizza;
        };
		virtual Pizza* createPizza(string) = 0; // factory method
};

class NYStyleCheesePizza : public Pizza {
	public:
		NYStyleCheesePizza(){
            name = "NY Style Sauce and Cheese Pizza";
            dough = "Thin Crust Dough";
            sauce = "Marinara Sauce";
            toppings.push_back("Grated Reggiano Chesse");
        };
};

class NYStyleClamPizza : public Pizza {
	public:
		NYStyleClamPizza(){
            name = "NY Style Clam Pizza";
            dough = "Thin Crust Dough";
            sauce = "Marinara Sauce";
            toppings.push_back("Grated Reggiano Cheese");
            toppings.push_back("Fresh Clams from Long Island Sound");
        };
};

class NYStylePepperoniPizza : public Pizza{
public:
	NYStylePepperoniPizza(){
        name = "NY Style Pepperoni Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";
    
        toppings.push_back("Grated Reggiano Cheese");
        toppings.push_back("Sliced Pepperoni");
        toppings.push_back("Garlic");
        toppings.push_back("Onion");
        toppings.push_back("Mushrooms");
        toppings.push_back("Red Pepper");
    };
};

class NYStyleVeggiePizza : public Pizza {
public:
    NYStyleVeggiePizza(){
        name = "NY Style Veggie Pizza";
        dough = "Thin Crust Dough";
        sauce = "Marinara Sauce";
        toppings.push_back("Grated Reggiano Cheese");
        toppings.push_back("Garlic");
        toppings.push_back("Onion");
        toppings.push_back("Mushrooms");
        toppings.push_back("Red Pepper");
    };
};

class NYPizzaStore : public PizzaStore {
public:
    Pizza* createPizza(string item) override{
        if (item == "cheese") return new NYStyleCheesePizza();
        else if (item == "veggie") return new NYStyleVeggiePizza();
        else if (item == "clam") return new NYStyleClamPizza();
        else if (item == "pepperoni") return new NYStylePepperoniPizza();
        return NULL;
    };
};



class ChicagoStyleCheesePizza : public Pizza {
	public:
		ChicagoStyleCheesePizza(){
            name = "Chicago Style Deep Dish Cheese Pizza";
            dough = "Extra Thick Crust Dough";
            sauce = "Plum Tomato Sauce";
            toppings.push_back("Shredded Mozzarella Cheese");
        };
		void cut() override{ cout << "cutting the pizza into square slices\n"; };
};

class ChicagoStyleClamPizza : public Pizza {
	public:
		ChicagoStyleClamPizza (){
            name = "Chicago Style Clam Pizza";
            dough = "Extra Thick Crust Dough";
            sauce = "Plum Tomato Sauce";
            toppings.push_back("Shredded Mozzarella Cheese");
            toppings.push_back("Frozen Clams from Chesapeake Bay");
        };
		void cut() override{ cout << "Cutting the pizza into square slices"; };
};

class ChicagoStylePepperoniPizza : public Pizza {
	public:
		ChicagoStylePepperoniPizza (){
            name = "Chicago Style Pepperoni Pizza";
            dough = "Extra Thick Crust Dough";
            sauce = "Plum Tomato Sauce";
            toppings.push_back("Shredded Mozzarella Cheese");
            toppings.push_back("Black Olives");
            toppings.push_back("Spinach");
            toppings.push_back("Eggplant");
            toppings.push_back("Sliced Pepperoni");
        };
		void cut() override{ cout << "Cutting the pizza into square slices\n"; };
};

class ChicagoStyleVeggiePizza : public Pizza {
	public:
		ChicagoStyleVeggiePizza (){
            name = "Chicago Deep Dish Veggie Pizza";
            dough = "Extra Thick Crust Dough";
            sauce = "Plum Tomato Sauce";
            toppings.push_back("Shredded Mozzarella Cheese");
            toppings.push_back("Black Olives");
            toppings.push_back("Spinach");
            toppings.push_back("Eggplant");
        };
};

class ChicagoPizzaStore : public PizzaStore {
public:
    Pizza* createPizza(string item) override{
        if (item == "cheese") return new ChicagoStyleCheesePizza();
        else if (item == "veggie") return new ChicagoStyleVeggiePizza();
        else if (item == "clam") return new ChicagoStyleClamPizza();
        else if (item == "pepperoni") return new ChicagoStylePepperoniPizza();
        return NULL;
    };
};


int main() {
	PizzaStore* nyStore = new NYPizzaStore();
	PizzaStore* chicagoStore = new ChicagoPizzaStore();

	Pizza* pizza = nyStore->pizzaOrder("cheese");
	cout << "Ethan orderd a " << pizza->getName() << "\n\n";

	pizza = chicagoStore->pizzaOrder("cheese");
	cout << "Joel orderd a " << pizza->getName() << "\n\n";

	pizza = nyStore->pizzaOrder("clam");
	cout << "Ethan orderd a " << pizza->getName() << "\n\n";

	pizza = chicagoStore->pizzaOrder("clam");
	cout << "Joel orderd a " << pizza->getName() << "\n\n";

	pizza = chicagoStore->pizzaOrder("pepperoni");
	cout << "Ethan orderd a " << pizza->getName() << "\n\n";

	pizza = chicagoStore->pizzaOrder("pepperoni");
	cout << "Joel orderd a " << pizza->getName() << "\n\n";

	pizza = chicagoStore->pizzaOrder("veggie");
	cout << "Ethan orderd a " << pizza->getName() << "\n\n";

	pizza = chicagoStore->pizzaOrder("veggie");
	cout << "Joel orderd a " << pizza->getName() << "\n\n";
	return 0;
}