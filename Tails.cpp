#include "Tails.h"


#include <SFML/Graphics.hpp>

Tails::Tails() {

    hitboxFlying = sf::FloatRect(posX, posY, 100, 100);

    flyingLeftTexture.loadFromFile("Data/fly_together_left.png");
    hitboxNormal = sf::FloatRect(posX, posY, 20, 100);
    currentHitbox = &hitboxNormal;
    flyingLeftSprite.setTexture(flyingLeftTexture);
    flyingLeftSprite.setScale(1, 0.5f);

    flyingRightTexture.loadFromFile("Data/fly_together_right.png");
    hitboxNormal = sf::FloatRect(posX, posY, 20, 100);
    currentHitbox = &hitboxNormal;
    flyingRightSprite.setTexture(flyingRightTexture);
    flyingRightSprite.setScale(1, 0.5f);
    // Ball animation — from ballRight.png / ballLeft.png
    ballFrameIndex = 0;
    ballFrameWidth = 236 / 6;     // = 39 (confirmed)
    ballFrameHeight = 38;
    ballFrameCount = 6;
    ballFrameTime = 0.1f;
    ballFrameTimer = 0.0f;

    // Jog animation — from rightJog.png / leftJog.png
    leftRightFrameTimer = 0.0f;
    leftRightFrameIndex = 0;
    leftRightFrameTime = 0.1f;
    leftRightFrameCount = 10;
    leftRightFrameWidth = 392 / 10;  // = 39
    leftRightFrameHeight = 38;

    // Fast run animation — from rightRunFast.png / leftRunFast.png
    runSpeedThreshold = 10.0f;
    leftRightFastFrameTimer = 0.0f;
    leftRightFastFrameIndex = 0;
    leftRightFastFrameTime = 0.1f;
    leftRightFastFrameCount = 8;
    leftRightFastFrameWidth = 312 / 8;  // = 39
    leftRightFastFrameHeight = 40;


    // Initialize player attributes
    isFastRun = false;

    velocityX = 2;
    velocityY = 0;

    acceleration = 0.2f;
    deacceleration = -1.0f;
    gravity = 1.0f;
    health = 3;
    isFlying = false;
    onGround = false;
    int raw_img_x = 24;
    int raw_img_y = 35;

    playerHeight = raw_img_y * 2.5;
    playerWidth = raw_img_x * 2.5;

    isBallForm = false;
    terminalVelocity = 12.0f;

    // Load textures
    leftTexture.loadFromFile("Data/tails/leftJog.png");
    rightTexture.loadFromFile("Data/tails/rightJog.png");
    ballRightTexture.loadFromFile("Data/tails/ballRight.png");  // ball textures
    ballLeftTexture.loadFromFile("Data/tails/ballLeft.png");    // ball textures
    leftFastTexture.loadFromFile("Data/tails/leftRunFast.png");
    rightFastTexture.loadFromFile("Data/tails/rightRunFast.png");
    leftStopTexture.loadFromFile("Data/tails/leftStop.png");
    rightStopTexture.loadFromFile("Data/tails/rightStop.png");


    // Set up hitboxes
    hitboxNormal = sf::FloatRect(posX, posY, 20, 20);
    hitboxBall = sf::FloatRect(posX, posY, 5, 5);
    currentHitbox = &hitboxNormal;
    // Set up sprites

    spriteMain.setTexture(leftTexture);
    spriteMain.setScale(3, 3);
    spriteLeft.setTexture(leftTexture);
    spriteLeft.setScale(3, 3);
    spriteRight.setTexture(rightTexture);
    spriteRight.setScale(3, 3);
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
    leadIsFlying = false;

}

void Tails::useAbility(char** lvl, float& offset_y, float cell_size) {
    static bool abilityInUse = false;
    static sf::Clock abilityClock;  // To track the time for ability cooldown

    // Check if the ability can be activated (after cooldown period)
    if (!abilityInUse && sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        isFlying = true;  // Activate flying ability
        abilityInUse = true;  // Mark ability as in use
        abilityClock.restart();  // Start the cooldown timer
        cout << "Flying activated!" << endl;
    }

    // Check if the ability's cooldown has finished
    if (abilityInUse && abilityClock.getElapsedTime().asSeconds() >= 7.0f) { //flying is of 7 seconds
        isFlying = false;  // Deactivate flying ability
        abilityInUse = false;  // Reset ability status, allowing it to be activated again
        cout << "Flying deactivated!" << endl;
        velocityY = 30.0f;
    }
}

void Tails::usePowerUp(char** lvl, float& offset_y, float cell_size) {

    //same above function copy[aasted

    static bool isAbilityActive = false;
    static sf::Clock powerUpClock;  // To track the time for ability cooldown


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
            lvl[rowMid + 1][colLeft] = 'g';

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
        isFlyingPowerUp = true;  // Activate flying ability
    }

    if ((powerUpClock.getElapsedTime().asSeconds() >= 4.0f) && (!isFlying)) { // so the ability doesn't hamper with flying
        isAbilityActive = false;
        isFlyingPowerUp = false;  // Deactivate flying ability
    }
}
