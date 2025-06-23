#ifndef PROJECTILE_H
#define PROJECTILE_H

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"

class Projectile {
public:
    // Constructor
    Projectile(Enemy* enemy);

    // Setters and Getters
    void setPosition(float x, float y);
    float getPosX() const;
    float getPosY() const;

    // Move the projectile
    void move(Player* player, sf::Clock& deltaClock, char** lvl, int mapWidth, int mapHeight, int cellSize);

    // Draw the projectile on the screen
    void draw(sf::RenderWindow& window, float cameraOffsetX, float cameraOffsetY);

private:
    float posX, posY;
    float initialPosX, initialPosY;
    const float speed = 700.0f;
    bool isTransparent;
    float elapsedTime = 0.0f;  // <- Add this line
    Enemy* enemy;
    sf::Sprite sprite;
    sf::Texture projectileTexture;

    float velocityX, velocityY;
    sf::Texture transparentTexture;
    sf::Clock internalClock;


};

#endif PROJECTILE_H
