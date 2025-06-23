
#ifndef KNUCKLES_H
#define KNUCKLES_H


#include "Player.h"
class Knuckles : public Player
{
private:
	Clock powerUpClock;
	bool isAbilityActive = false;
public:

	Knuckles();

	void useAbility(char** lvl, float& offset_y, float cell_size);
	void usePowerUp(char** lvl, float& offset_y, float cell_size) override;
};
#endif KNUCKLES_H

