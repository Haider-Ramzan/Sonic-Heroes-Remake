

#ifndef TAILS_H
#define TAILS_H

#include "Player.h"
class Tails : public Player
{
public:

	Tails();
	void useAbility(char** lvl, float& offset_y, float cell_size);
	void usePowerUp(char** lvl, float& offset_y, float cell_size) override;


};

#endif TAILS_H