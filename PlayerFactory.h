
#ifndef PLAYERFACTORY_H
#define PLAYERFACTORY_H


#include "Player.h"
#include "Sonic.h"
#include "Knuckles.h"
#include "Tails.h"
#include <SFML/Graphics.hpp>

class PlayerFactory
{
public:
	Player* createPlayer(const std::string& type);
};
#endif PLAYERFACTORY_H
