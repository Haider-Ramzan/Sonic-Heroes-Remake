#include "Sonic.h"

Sonic::Sonic() {
    // Ball animation
    ballFrameIndex = 0;
    ballFrameWidth = 40;         // pixels per frame
    ballFrameHeight = 40;        // assumed fixed height of each frame
    ballFrameCount = 8;          // number of frames in sheet
    ballFrameTime = 0.1f;        // seconds per frame
    ballFrameTimer = 0.0f;
    leadIsFlying = false;
    // Jog animation
    leftRightFrameTimer = 0.0f;
    leftRightFrameIndex = 0;
    leftRightFrameTime = 0.1f;       // Time per frame in seconds
    leftRightFrameCount = 10;        // Adjust based on the number of frames
    leftRightFrameWidth = 40;        // Width of each frame 
    leftRightFrameHeight = 40;       // Height of each frame 

    // Fast run animation
    runSpeedThreshold = 10.0f;
    leftRightFastFrameTimer = 0.0f;
    leftRightFastFrameIndex = 0;
    leftRightFastFrameTime = 0.1f;   // Time per frame in seconds
    leftRightFastFrameCount = 8;     // Adjust based on the number of frames
    leftRightFastFrameWidth = 40;    // Width of each frame 
    leftRightFastFrameHeight = 40;   // Height of each frame


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
    terminalVelocity = 18.0f;
    // Load textures
    leftTexture.loadFromFile("Data/0jog_Left.png");
    rightTexture.loadFromFile("Data/0jog_Right.png");
    ballRightTexture.loadFromFile("Data/0upR.png"); //ball textures
    ballLeftTexture.loadFromFile("Data/0upL.png"); //ball textures
    leftFastTexture.loadFromFile("Data/0left_run.png");
    rightFastTexture.loadFromFile("Data/0right_run.png");
    leftStopTexture.loadFromFile("Data/0left_still.png");
    rightStopTexture.loadFromFile("Data/0right_still.png");
    // Set up hitboxes
    hitboxNormal = sf::FloatRect(posX, posY, 20, 12.5);
    hitboxBall = sf::FloatRect(posX, posY, 5, 5);
    currentHitbox = &hitboxNormal;
    // Set up sprites

    spriteMain.setTexture(leftTexture);
    spriteMain.setScale(2.5, 2.5);
    spriteLeft.setTexture(leftTexture);
    spriteLeft.setScale(2.5, 2.5);
    spriteRight.setTexture(rightTexture);
    spriteRight.setScale(2.5, 2.5);
    spriteRightBall.setTexture(ballRightTexture);
    spriteRightBall.setScale(2.5, 2.5);
    spriteLeftBall.setTexture(ballLeftTexture);
    spriteLeftBall.setScale(2.5, 2.5);
    spriteRightRun.setTexture(rightFastTexture);
    spriteRightRun.setScale(2.5, 2.5);
    spriteLeftRun.setTexture(leftFastTexture);
    spriteLeftRun.setScale(2.5, 2.5);
    spriteLeftStop.setTexture(leftStopTexture);
    spriteLeftStop.setScale(2.5, 2.5);
    spriteRightStop.setTexture(rightStopTexture);
    spriteRightStop.setScale(2.5, 2.5);

    transparentTexture.loadFromFile("Data/transparent.png");
    transparentSprite.setTexture(transparentTexture);
    transparentSprite.setScale(2.5, 2.5);
}

void Sonic::useAbility(char** lvl, float& offset_y, float cell_size) {

    // Trigger ability if F is pressed and it's not already active
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && !isAbilityActive) {
        isAbilityActive = true;
        originalTerminalVelocity = terminalVelocity;
        terminalVelocity *= 1.5f; // increase Sonic's maximum speed

        //FYI Haider/Hassaan. Agar tum logon ko immediate effect tang kr rha hai, comment this if-else
        if (lastDirectionRight) {
            setVelocityX(terminalVelocity);
        }
        else setVelocityX(-terminalVelocity);


        abilityClock.restart();
        std::cout << "Sonic's speed ability activated!" << std::endl;
    }

    // Check if ability time is over
    if (isAbilityActive && abilityClock.getElapsedTime().asSeconds() >= 6.0f) {
        terminalVelocity = originalTerminalVelocity; // Restore normal speed
        isAbilityActive = false;
        std::cout << "Sonic's speed ability ended." << std::endl;
    }

}

void Sonic::usePowerUp(char** lvl, float& offset_y, float cell_size) {

	//same functions as above but speed increased by 4 instead of multiplying by 1.5 as stated in manual
  
    // Trigger ability if F is pressed and it's not already active

    float newPosX = posX + velocityX;

    float leftEdge = newPosX - 10;// this was done so that sonic can not get in the wall
    float rightEdge = newPosX + playerWidth + 20;

    float midY = posY;

    int rowMid = static_cast<int>(midY) / cell_size;
    int colLeft = static_cast<int>(leftEdge) / cell_size;
    int colRight = static_cast<int>(rightEdge) / cell_size;


    // Checking left or right side collisions
    bool collision = false;
    if (velocityX < 0) {
        // moving left: test left edge at top, mid, bottom
        if (lvl[rowMid][colLeft] == 'h' ||
            lvl[rowMid + 1][colLeft] == 'h')
        {
			lvl[rowMid][colLeft] = 'g'; // remove the powerup from the map
			lvl[rowMid + 1][colLeft] = 'g';
            collision = true;
        }
    }
    else if (velocityX > 0) {
        // moving right: test right edge
        if (lvl[rowMid][colRight] == 'h' ||
            lvl[rowMid + 1][colRight] == 'h')
        {
			lvl[rowMid][colRight] = 'g'; // remove the powerup from the map
			lvl[rowMid + 1][colRight] = 'g';
            collision = true;
        }
    }


    if ((collision) && !isAbilityActive) {
        isAbilityActive = true;
        originalTerminalVelocity = terminalVelocity;
        terminalVelocity += 4.0f; // increase Sonic's maximum speed

        //FYI Haider/Hassaan. Agar tum logon ko immediate effect tang kr rha hai, comment this if-else
        if (lastDirectionRight) {
            setVelocityX(terminalVelocity);
        }
        else setVelocityX(-terminalVelocity);


        abilityClock.restart();
        std::cout << "Sonic's speed ability activated!" << std::endl;
    }

    // Check if ability time is over
    if (isAbilityActive && abilityClock.getElapsedTime().asSeconds() >= 5.0f) {
        terminalVelocity = originalTerminalVelocity; // Restore normal speed
        isAbilityActive = false;
        std::cout << "Sonic's speed ability ended." << std::endl;
    }
}
