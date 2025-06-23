
#ifndef POWERUP_H
#define POWERUP_H

#include "Collectables.h"

class PowerUp : public Collectables
{
public:
	PowerUp();
	~PowerUp() {}
	bool setTexture(const std::string& filepath);

	sf::Sprite& getSprite();

	sf::Texture& getTexture();

};
#endif POWERUP_H

