#pragma once
#include "Motobug.h"
#include "Player.h"

#include <iostream>
using namespace std;

Motobug::Motobug(float x, float y) : CrawlingEnemy() {
    health = 2;
    collisionCooldown = 5.0f;
    timeSinceLastCollision = 0;
    posX = x;
    posY = y;
    velocityX = 8.0f;
    speed = velocityX;
    velocityY = 0;
    movingRight = true;
    sprite.setPosition(posX, posY);
    if (!texture.loadFromFile("Data/MotoBug.png")) {
        cout << "NOT LOADED - CrabMeat" << endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);
}

void Motobug::move(char** lvl, int cellSize, int mapWidth, int mapHeight, Player* player) {
    // Compute tile positions
    int rowMid = static_cast<int>(posY) / cellSize;
    int colLeft = static_cast<int>(posX - 1) / cellSize;
    int colRight = static_cast<int>(posX + cellSize) / cellSize;
    int colBug = static_cast<int>(posX) / cellSize;
    int colPlayer = static_cast<int>(player->getPosX()) / cellSize;

    // Clamp boundaries
    if (rowMid < 0) rowMid = 0;
    if (rowMid >= mapHeight - 1) rowMid = mapHeight - 2;
    if (colLeft < 0) colLeft = 0;
    if (colRight >= mapWidth) colRight = mapWidth - 1;

    // Decide direction based on player position
    if (colPlayer < colBug) velocityX = -speed;
    else if (colPlayer > colBug) velocityX = speed;
    else velocityX = 0;

    // Obstacle detection only in direction of movement
    bool obstacleFound = false;
    if (velocityX < 0) { // Moving left
        for (int c = colBug - 1; c >= colPlayer && c >= 0; --c) {
            if (lvl[rowMid][c] == 'w' || lvl[rowMid + 1][c] == 'w' ||
                lvl[rowMid][c] == 's' || lvl[rowMid + 1][c] == 's' ||
                lvl[rowMid][c] == 'b' || lvl[rowMid + 1][c] == 'b') {
                obstacleFound = true;
                break;
            }
        }
    }
    else if (velocityX > 0) { // Moving right
        for (int c = colBug + 1; c <= colPlayer && c < mapWidth; ++c) {
            if (lvl[rowMid][c] == 'w' || lvl[rowMid + 1][c] == 'w' ||
                lvl[rowMid][c] == 's' || lvl[rowMid + 1][c] == 's' ||
                lvl[rowMid][c] == 'b' || lvl[rowMid + 1][c] == 'b') {
                obstacleFound = true;
                break;
            }
        }
    }

    if (obstacleFound) {
        velocityX = 0;
    }

    // Move
    posX += velocityX;

    // Update sprite position
    sprite.setPosition(posX, posY);
}



void Motobug::update(char** lvl, int cellSize, int mapWidth, int mapHeight, float deltaTime, Player* player) {
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
                //std::cout << "Player hit CrabMeat!" << std::endl; // Debug message
                this->takeDamage(); // CrabMeat takes damage when hit by player in ball form
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
                std::cout << "Player hit CrabMeat!" << std::endl; // Debug message
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
                //std::cout << "CrabMeat hit Player!" << std::endl; // Debug message
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
                //std::cout << "Player hit CrabMeat!" << std::endl; // Debug message
                this->takeDamage(); // CrabMeat takes damage when hit by player in ball form
                timeSinceLastCollision = 0.0f;
            }
        }

        // Reset the time since last collision after the 
    }
}

void Motobug::attack() {
    std::cout << "Motobug attacks\n";
}

void Motobug::takeDamage() {
    health--;
    //cout << "TRALALLALALALLALALALALALAL " << endl;
}

Motobug::~Motobug() {}