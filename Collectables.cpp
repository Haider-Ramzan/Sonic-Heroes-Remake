#include "Collectables.h"


// Constructor
Collectables::Collectables() {}

// Destructor
Collectables::~Collectables() {}

// Load texture and set it to sprite
bool Collectables::setTexture(const std::string& filepath) {
    if (!texture.loadFromFile(filepath))
        return false;
    sprite.setTexture(texture);
    return true;
}

// Set the position of the sprite
void Collectables::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

// Get the sprite
sf::Sprite& Collectables::getSprite() {
    return sprite;
}

// Get the texture
sf::Texture& Collectables::getTexture() {
    return texture;
}

