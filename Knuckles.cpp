#include "Knuckles.h"


#include <SFML/Graphics.hpp>

Knuckles::Knuckles() {
    leadIsFlying = false;


    ballFrameIndex = 0;
    ballFrameWidth = 39;         // 628 / 16
    ballFrameHeight = 39;        // image height
    ballFrameCount = 16;         // number of frames
    ballFrameTime = 0.1f;        // seconds per frame
    ballFrameTimer = 0.0f;

    // Jog animation — from rightJog.png
    leftRightFrameTimer = 0.0f;
    leftRightFrameIndex = 0;
    leftRightFrameTime = 0.1f;
    leftRightFrameCount = 8;
    leftRightFrameWidth = 49;         // from 391 / 8
    leftRightFrameHeight = 51;        // from image height

    // Fast run animation — from rightRunFast.png
    runSpeedThreshold = 10.0f;
    leftRightFastFrameTimer = 0.0f;
    leftRightFastFrameIndex = 0;
    leftRightFastFrameTime = 0.1f;
    leftRightFastFrameCount = 5;
    leftRightFastFrameWidth = 39;     // from 196 / 5
    leftRightFastFrameHeight = 40;    // from image height


    // Initialize player attributes
    isFastRun = false;

    velocityX = 2;
    velocityY = 0;

    acceleration = 0.2f;
    deacceleration = -1.0f;
    gravity = 1.0f;
    health = 3;
    //isFlying = false;
    onGround = false;
    int raw_img_x = 24;
    int raw_img_y = 35;

    playerHeight = raw_img_y * 2.5;
    playerWidth = raw_img_x * 2.5;

    isBallForm = false;
    terminalVelocity = 12.0f;

    // Load textures
    leftTexture.loadFromFile("Data/knuckles/leftJog.png");
    rightTexture.loadFromFile("Data/knuckles/rightJog.png");
    ballRightTexture.loadFromFile("Data/knuckles/ballRight.png"); //ball textures
    ballLeftTexture.loadFromFile("Data/knuckles/ballLeft.png"); //ball textures
    leftFastTexture.loadFromFile("Data/knuckles/leftRunFast.png");
    rightFastTexture.loadFromFile("Data/knuckles/rightRunFast.png");
    leftStopTexture.loadFromFile("Data/knuckles/leftStop.png");
    rightStopTexture.loadFromFile("Data/knuckles/rightStop.png");

    // Set up hitboxes
    hitboxNormal = sf::FloatRect(posX, posY, 20, 12.5);
    hitboxBall = sf::FloatRect(posX, posY, 5, 5);
    currentHitbox = &hitboxNormal;
    // Set up sprites

    spriteMain.setTexture(leftTexture);
    spriteMain.setScale(3, 3);
    spriteLeft.setTexture(leftTexture);
    spriteLeft.setScale(2.5, 2.5);
    spriteRight.setTexture(rightTexture);
    spriteRight.setScale(2.5, 2.5);
    spriteRightBall.setTexture(ballRightTexture);
    spriteRightBall.setScale(3, 3);
    spriteLeftBall.setTexture(ballLeftTexture);
    spriteLeftBall.setScale(3, 3);
    spriteRightRun.setTexture(rightFastTexture);
    spriteRightRun.setScale(3, 3);
    spriteLeftRun.setTexture(leftFastTexture);
    spriteLeftRun.setScale(3, 3);
    spriteLeftStop.setTexture(leftStopTexture);
    spriteLeftStop.setScale(3, 3);
    spriteRightStop.setTexture(rightStopTexture);
    spriteRightStop.setScale(3, 3);

    transparentTexture.loadFromFile("Data/transparent.png");
    transparentSprite.setTexture(transparentTexture);
    transparentSprite.setScale(2.5, 2.5);
}

void Knuckles::useAbility(char** lvl, float& offset_y, float cell_size) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        float newPosX = posX + velocityX;


        float leftEdge = newPosX;
        float rightEdge = newPosX + playerWidth +20;

        float midY = posY;

        int rowMid = static_cast<int>(midY) / cell_size;
        int colLeft = static_cast<int>(leftEdge) / cell_size;
        int colRight = static_cast<int>(rightEdge) / cell_size;


        if (lvl[rowMid + 1][colLeft] == 'b') {
            lvl[rowMid + 1][colLeft] = 'g';
        }

        else if (lvl[rowMid + 1][colRight] == 'b') {
            lvl[rowMid + 1][colRight] = 'g';
        }

        else if (lvl[rowMid][colLeft] == 'b') {
            lvl[rowMid][colLeft] = 'g';
        }
        else if (lvl[rowMid][colRight] == 'b') {
            lvl[rowMid][colRight] = 'g';
        }

        else if (lvl[rowMid - 1][colLeft] == 'b') {
            lvl[rowMid - 1][colLeft] = 'g';
        }
        else if (lvl[rowMid - 1][colRight] == 'b') {
            lvl[rowMid - 1][colRight] = 'g';
        }

    }
}

void Knuckles::usePowerUp(char** lvl, float& offset_y, float cell_size) {

    float newPosX = posX + velocityX;

    float leftEdge = newPosX - 10;// this was done so that sonic can not get in the wall
    float rightEdge = newPosX + playerWidth + 20;

    float midY = posY;

    int rowMid = static_cast<int>(midY) / cell_size;
    int colLeft = static_cast<int>(leftEdge) / cell_size;
    int colRight = static_cast<int>(rightEdge) / cell_size;


    if (velocityX < 0) {
        // moving left: test left edge at top, mid, bottom
        if (lvl[rowMid][colLeft] == 'h' ||
            lvl[rowMid + 1][colLeft] == 'h')
        {
            lvl[rowMid][colLeft] = 'g'; // remove the powerup from the map

			isAbilityActive = true;
        }
        else {
			isAbilityActive = false;
        }
    }
    else if (velocityX > 0) {
        // moving right: test right edge
        if (lvl[rowMid][colRight] == 'h' ||
            lvl[rowMid + 1][colRight] == 'h')
        {
            lvl[rowMid][colRight] = 'g'; // remove the powerup from the map
            lvl[rowMid + 1][colRight] = 'g';
			isAbilityActive = true;
        }
        else {
			isAbilityActive = false;
        }
    }


   

	if (isAbilityActive) {
        powerUpClock.restart();
		isInvincible = true; // Set invincibility flag
	}

    if (powerUpClock.getElapsedTime().asSeconds() >= 15.0f) {
        
        isAbilityActive = false;
        isInvincible = false; // Reset invincibility flag
    }

	
}