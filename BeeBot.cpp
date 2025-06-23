#pragma once
#include "BeeBot.h"
#include "Player.h"

#include <iostream>
using namespace std;

BeeBot::BeeBot(float x, float y) : FlyingEnemy() {
    health = 2;
    collisionCooldown = 5.0f;
    timeSinceLastCollision = 0;
    posX = x;
    posY = y;
    initialY = y;
    velocityX = 1.5f;
    speed = velocityX;
    velocityY = 1.5f;
    movingRight = true;
    sprite.setPosition(posX, posY);
    if (!texture.loadFromFile("Data/BeeBot.png")) {
        cout << "NOT LOADED - BeeBot" << endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);
    projectileThrower = true;

}

void BeeBot::move(char** lvl, int cellSize, int mapWidth, int mapHeight, Player* player) {
    int row = static_cast<int>(posY) / cellSize;
    int col = static_cast<int>(posX) / cellSize;

    // Clamp row
    if (row < 0) row = 0;
    if (row >= mapHeight - 1) row = mapHeight - 2;

    // Default velocities
    velocityX = movingRight ? speed : -speed;
    velocityY = 0;

    // Predict next tile horizontally
    int nextCol = static_cast<int>(posX + velocityX + (velocityX > 0 ? cellSize : -1)) / cellSize;
    nextCol = std::max(0, std::min(nextCol, mapWidth - 1));

    // Check for obstacle
    bool xBlocked = false;
    if (lvl[row][nextCol] == 'w' || lvl[row + 1][nextCol] == 'w' ||
        lvl[row][nextCol] == 's' || lvl[row + 1][nextCol] == 's' ||
        lvl[row][nextCol] == 'b' || lvl[row + 1][nextCol] == 'b') {
        xBlocked = true;
    }

    // Reverse direction if blocked
    if (xBlocked) {
        movingRight = !movingRight;
        velocityX = -velocityX;
    }

    // Horizontal move
    posX += velocityX;

    // Zigzag vertical move (sine wave)
    zigzagTimer += zigzagSpeed;
    posY = initialY + sin(zigzagTimer) * zigzagAmplitude;

    // Set sprite position
    sprite.setPosition(posX, posY);
}

void BeeBot::update(char** lvl, int cellSize, int mapWidth, int mapHeight, float deltaTime, Player* player) {
    // Move CrabMeat and update sprite position
    move(lvl, cellSize, mapWidth, mapHeight, player);

    // Increment the time since the last collision
    timeSinceLastCollision += deltaTime;

    // Check for collision only after the cooldown time (5 seconds)
    if (timeSinceLastCollision >= collisionCooldown) {
        // Collision logic (if player is in ball form)
        if (player->getIsBallForm()) {
            // Calculate the width of the player and CrabMeat
            float playerWidth = cellSize - 10;
            float crabWidth = cellSize - 10;

            // Calculate the horizontal and vertical distances
            float xDistance = player->getPosX() - posX;
            float yDistance = player->getPosY() - posY;

            // Check the height difference (within 60 pixels)
            bool withinHeight = (yDistance > -60 && yDistance < 60);

            // Check if the player is to the left or right of CrabMeat
            bool withinWidth = false;
            if (xDistance < 0) {
                // Player is to the left of CrabMeat: use player's width for the left-side check
                withinWidth = (xDistance > -(playerWidth)); // Add 10 to the difference
            }
            else {
                // Player is to the right of CrabMeat: use CrabMeat's width for the right-side check
                withinWidth = (xDistance < crabWidth + 10); // Add 10 to the difference
            }

            // If the player is within both the width and height range, take damage
            if (withinHeight && withinWidth) {
               
                this->takeDamage(); // CrabMeat takes damage when hit by player in ball form
                timeSinceLastCollision = 0.0f;
            }
        }
        else {
            // Calculate the width of the player and CrabMeat
            float playerWidth = cellSize - 10;
            float crabWidth = cellSize - 10;

            // Calculate the horizontal and vertical distances
            float xDistance = player->getPosX() - posX;
            float yDistance = player->getPosY() - posY;

            // Check the height difference (within 60 pixels)
            bool withinHeight = (yDistance > -60 && yDistance < 60);

            // Check if the player is to the left or right of CrabMeat
            bool withinWidth = false;
            if (xDistance < 0) {
                // Player is to the left of CrabMeat: use player's width for the left-side check
                withinWidth = (xDistance > -(playerWidth)); // Add 10 to the difference
            }
            else {
                // Player is to the right of CrabMeat: use CrabMeat's width for the right-side check
                withinWidth = (xDistance < crabWidth + 10); // Add 10 to the difference
            }

            // If the player is within both the width and height range, take damage
            if (withinHeight && withinWidth) {
                
                player->takeDamage(); // CrabMeat takes damage when hit by player in ball form
                timeSinceLastCollision = 0.0f;
            }
        }

        // Reset the time since last collision after the 
    }    if (timeSinceLastCollision >= collisionCooldown) {
        // Collision logic (if player is in ball form)
        if (player->getIsBallForm()) {
            // Calculate the width of the player and CrabMeat
            float playerWidth = cellSize - 10;
            float crabWidth = cellSize - 10;

            // Calculate the horizontal and vertical distances
            float xDistance = player->getPosX() - posX;
            float yDistance = player->getPosY() - posY;

            // Check the height difference (within 60 pixels)
            bool withinHeight = (yDistance > -60 && yDistance < 60);

            // Check if the player is to the left or right of CrabMeat
            bool withinWidth = false;
            if (xDistance < 0) {
                // Player is to the left of CrabMeat: use player's width for the left-side check
                withinWidth = (xDistance > -(playerWidth)); // Add 10 to the difference
            }
            else {
                // Player is to the right of CrabMeat: use CrabMeat's width for the right-side check
                withinWidth = (xDistance < crabWidth + 10); // Add 10 to the difference
            }

            // If the player is within both the width and height range, take damage
            if (withinHeight && withinWidth) {
                
                this->takeDamage(); // CrabMeat takes damage when hit by player in ball form
                timeSinceLastCollision = 0.0f;
            }
        }

        // Reset the time since last collision after the 
    }
}

void BeeBot::attack() {
    std::cout << "Motobug attacks\n";
}

void BeeBot::takeDamage() {
    health--;
    //cout << "TRALALLALALALLALALALALALAL " << endl;
}

BeeBot::~BeeBot() {}