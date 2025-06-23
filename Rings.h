
#ifndef RINGS_H
#define RINGS_H


#include <SFML/Graphics.hpp>
#include "Collectables.h"

class Rings : public Collectables {
public:
	Rings();
	~Rings() {} 

	bool setTexture(const std::string& filepath);

	void setPosition(float x, float y);
	sf::Sprite& getSprite();

	sf::Texture& getTexture();
};
#endif RINGS_H
