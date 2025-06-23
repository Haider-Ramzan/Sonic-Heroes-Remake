#include "PowerUp.h"


PowerUp::PowerUp()
{
	if (!texture.loadFromFile("Data/powerup.png"))
	{
	}
	sprite.setTexture(texture);
}

bool PowerUp::setTexture(const std::string& filepath)
{
	if (!texture.loadFromFile(filepath))
	{
		return false; // Failed to load texture
	}
	sprite.setTexture(texture);
	return true;
}

sf::Sprite& PowerUp::getSprite()
{
	return sprite;
}

sf::Texture& PowerUp::getTexture()
{
	return texture;
}