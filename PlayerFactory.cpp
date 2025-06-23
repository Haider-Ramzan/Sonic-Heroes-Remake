#include "PlayerFactory.h"


Player* PlayerFactory::createPlayer(const std::string& type)
{
	if (type == "Sonic")
	{
		return new Sonic();
	}
	else if (type == "Knuckles")
	{
		return new Knuckles();
	}
	else if (type == "Tails") {
		return new Tails();
	}
	// Add more player types here if needed
	return nullptr; // Return nullptr if the type is not recognized
}