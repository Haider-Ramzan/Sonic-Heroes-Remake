#include "BonusLife.h"



BonusLife::BonusLife()
{
	if (!texture.loadFromFile("Data/heart.png"))
	{
	}
	sprite.setTexture(texture);

}

bool BonusLife::setTexture(const std::string& filepath)
{
	if (!texture.loadFromFile(filepath))
	{
		return false; // Failed to load texture
	}
	sprite.setTexture(texture);
	return true;
}

sf::Sprite& BonusLife::getSprite()
{
	return sprite;
}
sf::Texture& BonusLife::getTexture()
{
	return texture;
}
