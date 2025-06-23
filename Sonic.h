

#ifndef SONIC_H
#define SONIC_H


#include "Player.h"
#include <SFML/Graphics.hpp>

class Sonic : public Player
{
	bool isAbilityActive = false;
	float originalTerminalVelocity;
	sf::Clock abilityClock;
public:
	Sonic();
	void useAbility(char** lvl, float& offset_y, float cell_size);
	void usePowerUp(char** lvl, float& offset_y, float cell_size) override;
};

#endif SONIC_H
