#pragma once
#include "CrabMeat.h"
#include "Player.h"

#include <iostream>
using namespace std;

CrabMeat::CrabMeat(float x, float y) : CrawlingEnemy() {
    health = 4;
    collisionCooldown = 5.0f;
    timeSinceLastCollision = 0;
    posX = x;
    posY = y;
    velocityX = 1.0f;
    velocityY = 0;
    movingRight = true;
    shootCooldown = 5.0f;
    timeSinceLastShot = 1.0f;
    sprite.setPosition(posX, posY);
    if (!texture.loadFromFile("Data/CrabMeat.png")) {
        cout << "NOT LOADED - CrabMeat" << endl;
    }
    sprite.setTexture(texture);
    sprite.setScale(1.0f, 1.0f);
    projectileThrower = true;
}

void CrabMeat::move(char** lvl, int cellSize, int mapWidth, int mapHeight, Player* player) {
    // Compute tile positions
    int rowMid = static_cast<int>(posY) / cellSize;
    int colLeft = static_cast<int>(posX - 1) / cellSize;
    int colRight = static_cast<int>(posX + cellSize) / cellSize;

    // Clamp boundaries
    if (rowMid < 0) rowMid = 0;
    if (rowMid >= mapHeight - 1) rowMid = mapHeight - 2;
    if (colLeft < 0) colLeft = 0;
    if (colRight >= mapWidth) colRight = mapWidth - 1;

    // Check for collision with terrain
    bool collision = false;

    if (velocityX < 0) { // Moving left
        if (lvl[rowMid][colLeft] == 'w' || lvl[rowMid + 1][colLeft] == 'w' ||
            lvl[rowMid][colLeft] == 's' || lvl[rowMid + 1][colLeft] == 's' ||
            lvl[rowMid][colLeft] == 'b' || lvl[rowMid + 1][colLeft] == 'b') {
            collision = true;
        }
    }
    else if (velocityX > 0) { // Moving right
        if (lvl[rowMid][colRight] == 'w' || lvl[rowMid + 1][colRight] == 'w' ||
            lvl[rowMid][colRight] == 's' || lvl[rowMid + 1][colRight] == 's' ||
            lvl[rowMid][colRight] == 'b' || lvl[rowMid + 1][colRight] == 'b') {
            collision = true;
        }
    }

    // Reverse direction if needed
    if (collision) {
        velocityX = -velocityX;
    }

    // Move
    posX += velocityX;

    //  Ensure sprite reflects new position
    sprite.setPosition(posX, posY);
}

void CrabMeat::shootProjectiles() {

}

void CrabMeat::update(char** lvl, int cellSize, int mapWidth, int mapHeight, float deltaTime, Player* player) {
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

    // Other game logic like shooting (as in your original example)
    timeSinceLastShot += deltaTime;
    if (timeSinceLastShot >= shootCooldown) {
        shootProjectiles();
        timeSinceLastShot = 0.0f;
    }
}

void CrabMeat::attack() {
    std::cout << "CrabMeat attacks\n";
}

void CrabMeat::takeDamage() {
    health--;
    //cout << "TRALALLALALALLALALALALALAL " << endl;
}

CrabMeat::~CrabMeat() {}