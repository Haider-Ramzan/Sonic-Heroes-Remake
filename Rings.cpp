#include "Rings.h"

Rings::Rings() {
	
	// Load the texture from file
	if (!texture.loadFromFile("Data/ring_one.png")) {
		// Handle error
	}
	sprite.setTexture(texture);
	sprite.setScale(4, 4);

}

 
bool Rings :: setTexture(const std::string& filepath) {
	if (!texture.loadFromFile(filepath))
		return false;
	sprite.setTexture(texture);
	return true;
}

void Rings :: setPosition(float x, float y) {
	sprite.setPosition(x, y);
}

sf::Sprite& Rings :: getSprite() {
	return sprite;
}

sf::Texture& Rings :: getTexture() {
	return texture;
}