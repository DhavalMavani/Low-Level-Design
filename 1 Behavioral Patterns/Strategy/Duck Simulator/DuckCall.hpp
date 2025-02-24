#ifndef DUCK_CALL_hpp
#define DUCK_CALL_hpp

#include "QuackBehavior.hpp"
#include "Quack.hpp"
#include <iostream>
#include <memory>

class DuckCall {
	public:
		DuckCall() { quackBehavior = std::make_unique<Quack>(); }
		void display() const { std::cout << "I'm not a duck!\n"; }
		void performQuack() { quackBehavior->quack(); }
	private:
		std::unique_ptr<QuackBehavior> quackBehavior;
};

#endif 