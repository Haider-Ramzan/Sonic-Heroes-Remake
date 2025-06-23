#include "CollectablesFactory.h"


Collectables* CollectablesFactory::createCollectable(std::string type) {
	if (type == "Rings") {
		return new Rings();
	}
	else if (type == "BonusLife") {
		return new BonusLife();
	}
	else if (type == "PowerUp") {
		return new PowerUp();
	}
	else {
		return nullptr; // or throw an exception
	}
}