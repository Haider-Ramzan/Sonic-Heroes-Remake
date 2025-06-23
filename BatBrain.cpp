#pragma once
#include "BatBrain.h"
#include "Player.h"

#include <iostream>
using namespace std;

BatBrain::BatBrain(float x, float y) : FlyingEnemy() {
    health = 2;
    collisionCooldown = 5.0f;
    timeSinceLastCollision = 0;
    posX = x;
    posY = y;
    velocityX = 1.5f;
    speed = velocityX;
    velocityY = 1.5f;
    movingRight = true;
    sprite.setPosition(posX, posY);
    if (!texture.loadFromFile("Data/BatBrain.png")) {
        cout << "NOT LOADED - CrabMeat" << endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(0.5f, 0.5f);
}

void BatBrain::move(char** lvl, int cellSize, int mapWidth, int mapHeight, Player* player) {
    // Compute tile positions
    int row = static_cast<int>(posY) / cellSize;
    int col = static_cast<int>(posX) / cellSize;
    int playerRow = static_cast<int>(player->getPosY()) / cellSize;
    int playerCol = static_cast<int>(player->getPosX()) / cellSize;

    // Clamp row
    if (row < 0) row = 0;
    if (row >= mapHeight - 1) row = mapHeight - 2;

    // Determine direction
    int dirX = 0;
    if (playerCol < col) dirX = -1;
    else if (playerCol > col) dirX = 1;

    int dirY = 0;
    if (playerRow < row) dirY = -1;
    else if (playerRow > row) dirY = 1;

    // Default: no movement
    velocityX = 0;
    velocityY = 0;

    // Compute target tile
    int nextCol = static_cast<int>(posX + dirX * speed + (dirX == 1 ? cellSize : -1)) / cellSize;
    int nextRow = static_cast<int>(posY + dirY * speed) / cellSize;

    // Clamp
    nextCol = std::max(0, std::min(nextCol, mapWidth - 1));
    nextRow = std::max(0, std::min(nextRow, mapHeight - 2));

    // Check horizontal movement
    bool xBlocked = false;
    if (dirX != 0) {
        if (lvl[row][nextCol] == 'w' || lvl[row + 1][nextCol] == 'w' ||
            lvl[row][nextCol] == 's' || lvl[row + 1][nextCol] == 's' ||
            lvl[row][nextCol] == 'b' || lvl[row + 1][nextCol] == 'b') {
            xBlocked = true;
        }
    }

    // If blocked horizontally, try going up
    if (xBlocked) {
        int upRow = static_cast<int>(posY - speed) / cellSize;
        if (upRow >= 0 &&
            lvl[upRow][col] != 'w' && lvl[upRow + 1][col] != 'w' &&
            lvl[upRow][col] != 's' && lvl[upRow + 1][col] != 's' &&
            lvl[upRow][col] != 'b' && lvl[upRow + 1][col] != 'b') {
            velocityY = -speed;
        }
    }
    else {
        velocityX = dirX * speed;
    }

    // Always try vertical follow if not already going up due to obstacle
    if (velocityY == 0 && dirY != 0) {
        if (lvl[nextRow][col] != 'w' && lvl[nextRow + 1][col] != 'w' &&
            lvl[nextRow][col] != 's' && lvl[nextRow + 1][col] != 's' &&
            lvl[nextRow][col] != 'b' && lvl[nextRow + 1][col] != 'b') {
            velocityY = dirY * speed;
        }
    }

    // Move
    posX += velocityX;
    posY += velocityY;

    // Update sprite
    sprite.setPosition(posX, posY);
}


void BatBrain::update(char** lvl, int cellSize, int mapWidth, int mapHeight, float deltaTime, Player* player) {
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

void BatBrain::attack() {

}

void BatBrain::takeDamage() {
    health--;
    //cout << "TRALALLALALALLALALALALALAL " << endl;
}

BatBrain::~BatBrain() {}