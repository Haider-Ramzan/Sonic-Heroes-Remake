#include "Projectile.h"
#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

Projectile::Projectile(Enemy* enemy) {
    this->enemy = enemy;
    velocityX = 700;
    velocityY = 0;

    // Default to (0,0) if enemy is nullptr
    if (enemy) {
        posX = enemy->getPosX();
        posY = enemy->getPosY();
    }
    else {
        posX = 0.0f;
        posY = 0.0f;
    }

    initialPosX = posX;
    initialPosY = posY;
    isTransparent = true;

    if (!projectileTexture.loadFromFile("Data/Projectile.png")) {
        std::cout << "Texture for Projectile not loaded!" << std::endl;
    }
    sprite.setTexture(projectileTexture);
    sprite.setPosition(posX, posY);
    sprite.setScale(0.25f, 0.25f); // Optional: adjust scale
    elapsedTime = 5.0f;
}

void Projectile::setPosition(float x, float y) {
    posX = x;
    posY = y;
    sprite.setPosition(posX, posY);
}

float Projectile::getPosX() const {
    return posX;
}

float Projectile::getPosY() const {
    return posY;
}



void Projectile::move(Player* player, sf::Clock& deltaClock, char** lvl, int mapWidth, int mapHeight, int cellSize) {
    float dt = internalClock.restart().asSeconds(); // Use internalClock instead
    elapsedTime += dt;


    // Handle transparency/reset logic
    if (isTransparent) {
        //sprite.setTexture(transparentTexture);
        //sprite.setPosition(posX, posY);
        //sprite.setScale(0.25f, 0.25f); // Optional: adjust scale
        if (elapsedTime >= 5.0f && enemy != nullptr) {
            posX = enemy->getPosX();
            posY = enemy->getPosY();

            if (posY < 600.0f) {
                velocityX = 0.0f;
                velocityY = 5;
            }
            else {
                float playerX = player->getPosX();
                velocityY = 0.0f;
                velocityX = (playerX < posX) ? -5 : 5;
                posY -= 100;
            }

            isTransparent = false;
            sprite.setTexture(projectileTexture);
            sprite.setPosition(posX, posY);
            sprite.setScale(0.25f, 0.25f); // Optional: adjust scale
            elapsedTime = 0.0f;
        }
        else {
            return;
        }
    }

    // Apply movement
    posX += velocityX;
    posY += velocityY;
    //cout << posX << "<" << posY << endl;

    // Get projectile dimensions
    float projW = sprite.getTexture()->getSize().x * sprite.getScale().x;
    float projH = sprite.getTexture()->getSize().y * sprite.getScale().y;

    // --- Vertical logic ---
    if (posY >= 850.0f) {
        posY = 850.0f;
        isTransparent = true;
        elapsedTime = 0.0f;
        //std::cout << "Projectile hit ground. Transparency triggered.\n";
    }

    // --- Horizontal logic ---
    for (int row = 0; row < mapHeight; ++row) {
        for (int col = 0; col < mapWidth; ++col) {
            if (lvl[row][col] == 'w' || lvl[row][col] == 's' || lvl[row][col] == 'b') {
                float blockX = col * cellSize;
                float blockY = row * cellSize;
                float blockW = cellSize;
                float blockH = cellSize;

                float margin = 70.0f; // How much smaller you want the hitbox

                bool intersects = (posX + margin < blockX + blockW &&
                    posX + projW - margin > blockX &&
                    posY + margin < blockY + blockH &&
                    posY + projH - margin > blockY);


                if (intersects) {
                    isTransparent = true;
                    elapsedTime = 0.0f;
                    std::cout << "Projectile hit wall. Transparency triggered.\n";
                    return;
                }
            }
        }
    }

    // --- Collision with player (manual AABB) ---
    float playerX = player->getPosX();
    float playerY = player->getPosY();
    float playerW = cellSize - 10;
    float playerH = cellSize - 10;

    bool hitPlayer = (posX < playerX + playerW &&
        posX + projW > playerX &&
        posY < playerY + playerH &&
        posY + projH > playerY);

    if (hitPlayer) {
        player->takeDamage();
        isTransparent = true;
        elapsedTime = 0.0f;
        std::cout << "Projectile hit player. Transparency triggered.\n";
    }
}



void Projectile::draw(sf::RenderWindow& window, float offsetX = 0, float offsetY = 0) {
    if (isTransparent) return; // Skip drawing if invisible
    sprite.setPosition(posX - offsetX, posY - offsetY);
    window.draw(sprite);
}

