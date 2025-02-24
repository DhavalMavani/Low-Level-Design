#include "Duck.hpp"
#include "MallardDuck.hpp"
#include "ModalDuck.hpp"
#include "FlyRocketPowered.hpp"
#include "DuckCall.hpp"
#include "MuteDuck.hpp"
#include <memory>

int main() {
	using DuckPtr = std::unique_ptr<Duck>; // type alias
	DuckPtr mallard = std::make_unique<MallardDuck>();
	mallard->performQuack();
	mallard->performFly();

	DuckPtr model = std::make_unique<ModalDuck>();
	model->performFly();
	model->setFlyBehavior(std::make_unique<FlyRocketPowered>());
	model->performFly();

	auto duckCall = DuckCall();
	duckCall.performQuack();
	duckCall.display();

	DuckPtr muteduck = std::make_unique<MuteDuck>();
	muteduck->performFly();
	muteduck->performQuack();
	muteduck->display();

	return 0;
};