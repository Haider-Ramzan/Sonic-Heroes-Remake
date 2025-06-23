
#ifndef BONUSLIFE_H
#define BONUSLIFE_H



#include "Collectables.h"

class BonusLife : public Collectables
{
public:
	BonusLife();
	~BonusLife() {}
	bool setTexture(const std::string& filepath);

	sf::Sprite& getSprite();

	sf::Texture& getTexture();
	
};

#endif BONUSLIFE_H

