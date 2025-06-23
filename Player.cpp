
#include <iostream>


/**/#include "Player.h"

#include "Animation.h" // Add this at the top of Player.cpp




int Player::health = 10; // Initialize static health variable

/*
Player::Player() {
}
*/


void Player::followPlayer(Player* leadPlayer, char** lvl, float cell_size, int levelWidth, int levelHeight, int difference = 0) {

    isLead = false; // Set this player as a follower

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && !isBallForm) {
        enterBallForm();
    }


    velocityX = leadPlayer->getVelocityX();
    if (!leadPlayer->isFlying) {
        velocityY = leadPlayer->getVelocityY();
    }

    if ((!leadPlayer->getIsFlying()) || (!leadPlayer->isFlyingPowerUp)) {
        leadIsFlying = false;
    }

    if ((leadPlayer->isFlying) || (leadPlayer->isFlyingPowerUp)) {
        leadIsFlying = true;
        spriteMain.setTexture(transparentTexture); // swap to transparent sprite
        return;
    }
    else if (velocityX < 0 && (spriteMain.getTexture() == spriteRight.getTexture()) || (spriteMain.getTexture() == spriteRightBall.getTexture())) { //if the ball is going right, but it should go left
        if (isBallForm) {
            spriteMain = spriteLeftBall;
        }
        else spriteMain = spriteLeft;
    }
    else if (velocityX > 0 && (spriteMain.getTexture() == spriteLeft.getTexture()) || (spriteMain.getTexture() == spriteLeftBall.getTexture())) { //if the ball is going right, but it should go left
        if (isBallForm) {
            spriteMain = spriteRightBall;
        }
        else spriteMain = spriteRight;
    }

    if (velocityX > 0) {
        lastDirectionRight = true;
    }
    if (velocityX < 0) {
        lastDirectionRight = false;
    }

    if (leadPlayer->isFlying && !sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        velocityY = velocityY;
    }
    else     if (leadPlayer->isFlying && sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
        posY = leadPlayer->posY;
        setVelocityY(0);
    }
    else if (!leadPlayer->onGround && onGround) {
        velocityY = -20.0f;
        onGround = false;
    }
    if (leadPlayer->onGround && leadPlayer->getVelocityY() == 0 && !onGround) {
        velocityY = 10.0f;
    }
    if (velocityX == 0 && onGround) {
        isFastRun = false;
        if (isBallForm) {
            exitBallForm();
        }
        if (!lastDirectionRight) {
            spriteMain = spriteLeftStop;
        }
        else spriteMain = spriteRightStop;
    }
    if (velocityX > 0) {
        if (velocityX > runSpeedThreshold) {
            isFastRun = true;  // Set to fast run state
        }
        else {
            isFastRun = false; // Set to normal run state
        }
    }
    else {
        if (-velocityX > runSpeedThreshold) {
            isFastRun = true;  // Set to fast run state
        }
        else {
            isFastRun = false; // Set to normal run state
        }
    }



    if (isFastRun && !isBallForm) {
        // If moving right with fast run
        if (velocityX > 0) {
            spriteMain = spriteRightRun; // Switch to fast run sprite
        }
        // If moving left with fast run
        else if (velocityX < 0) {
            spriteMain = spriteLeftRun; // Switch to fast run sprite
        }
    }
    else if (isBallForm) {
        // If moving right in normal run
        if (velocityX > 0) {
            spriteMain = spriteRightBall;
        }
        // If moving left in normal run
        else if (velocityX < 0) {
            spriteMain = spriteLeftBall;
        }
    }
    else {
        // If moving right in normal run
        if (velocityX > 0) {
            spriteMain = spriteRight; // Use normal right run sprite
        }
        // If moving left in normal run
        else if (velocityX < 0) {
            spriteMain = spriteLeft; // Use normal left run sprite
        }
    }

    // 3) Compute proposed new X position
    float newPosX = leadPlayer->posX + velocityX;

    if (leadPlayer->lastDirectionRight) {
        if (posX >= leadPlayer->getPosX() || abs(leadPlayer->getPosX() - posX) < difference) {
            return;
        }
        else newPosX -= difference;
    }
    else {
        if (posX <= leadPlayer->getPosX() || abs(leadPlayer->getPosX() - posX) < difference) {
            return;
        }
        else newPosX += difference;
    }


    /////////////////////////////////////the Hitbox colllisions from left and right/////////////////////////////////////////////////////////
    // finding the hitbox edges
    float leftEdge = newPosX;// this was done so that sonic can not get in the wall
    float rightEdge = newPosX + playerWidth + 20;

    float midY = posY;

    int rowMid = static_cast<int>(midY) / cell_size;
    int colLeft = static_cast<int>(leftEdge) / cell_size;
    int colRight = static_cast<int>(rightEdge) / cell_size;


    // Checking left or right side collisions
    bool collision = false;
    if (velocityX < 0) {
        // moving left: test left edge at top, mid, bottom
        if (lvl[rowMid][colLeft + 1] == 'w' ||
            lvl[rowMid + 1][colLeft + 1] == 'w')
        {
            collision = true;
        }
    }
    else if (velocityX > 0) {
        // moving right: test right edge
        if (lvl[rowMid][colRight - 1] == 'w' ||
            lvl[rowMid + 1][colRight - 1] == 'w')
        {
            collision = true;
        }
    }

    //collision with breakable wALLS
    if (velocityX < 0) {
        // moving left: test left edge at top, mid, bottom
        if (lvl[rowMid][colLeft + 1] == 'b' ||
            lvl[rowMid + 1][colLeft + 1] == 'b')
        {
            collision = true;
        }
    }
    else if (velocityX > 0) {
        // moving right: test right edge
        if (lvl[rowMid][colRight - 1] == 'b' ||
            lvl[rowMid + 1][colRight - 1] == 'b')
        {
            collision = true;
        }
    }


    //Resolve collision or apply movement
    if (!collision) {
        posX = newPosX;
    }
    else {
        // if collided, stop horizontal movement
        velocityX = 0;
    }



    // Back to normal form
    if (isBallForm && ballFormClock.getElapsedTime().asSeconds() >= ballDuration) {
        exitBallForm();
    }

    int playerLeft = static_cast<int>(posX) / cell_size;
    int playerRight = static_cast<int>(posX + playerWidth) / cell_size;
    int playerTop = static_cast<int>(posY) / cell_size;
    int playerBottom = static_cast<int>(posY + playerHeight) / cell_size;

    if ((lvl[playerTop][playerLeft] == 'w' || lvl[playerTop][playerRight] == 'w' ||
        lvl[playerBottom][playerLeft] == 'w' || lvl[playerBottom][playerRight] == 'w' ||
        lvl[playerTop][playerLeft] == 'b' || lvl[playerTop][playerRight] == 'b' ||
        lvl[playerBottom][playerLeft] == 'b' || lvl[playerBottom][playerRight] == 'b'))
    {
        if (posY <= 64) {
            posY += 64;
        }
        else {

            posY -= 64; // Move up one block
        }
    }
    else {
        posY = posY;
    }


    if (leadPlayer->posX <= 200) {
        posX = leadPlayer->posX;
    }






    //if (!leadPlayer->onGround && onGround) {
    //    velocityY = +20.0f;
    //    onGround = false;
    //}

}

void Player::move(char** lvl, float cell_size, int levelWidth, int levelHeight, int& ringScore) {

    isLead = true; // Set this player as the lead player

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::B) && !isBallForm) {
        enterBallForm();
    }

    // 1) Handle input and adjust velocityX
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        velocityX -= acceleration;

        if (velocityX < -terminalVelocity)
        {
            velocityX = -terminalVelocity;
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        velocityX += acceleration;
        if (velocityX > terminalVelocity)
        {
            velocityX = terminalVelocity;
        }
    }
    else { // deceleration when key not pressed

        if (velocityX > 0)
        {
            velocityX -= deacceleration * -1;
            if (velocityX < 0) velocityX = 0;
        }
        else if (velocityX < 0)
        {
            velocityX += deacceleration * -1;
            if (velocityX > 0) velocityX = 0;
        }

        if (velocityX < 0 && (spriteMain.getTexture() == spriteRight.getTexture()) || (spriteMain.getTexture() == spriteRightBall.getTexture())) { //if the ball is going right, but it should go left
            if (isBallForm) {
                spriteMain = spriteLeftBall;
            }
            else spriteMain = spriteLeft;
        }
        else if (velocityX > 0 && (spriteMain.getTexture() == spriteLeft.getTexture()) || (spriteMain.getTexture() == spriteLeftBall.getTexture())) { //if the ball is going right, but it should go left
            if (isBallForm) {
                spriteMain = spriteRightBall;
            }
            else spriteMain = spriteRight;
        }
    }

    if (velocityX > 0) {
        lastDirectionRight = true;
    }
    if (velocityX < 0) {
        lastDirectionRight = false;
    }


    if (velocityX == 0 && onGround) {
        isFastRun = false;
        if (isBallForm) {
            exitBallForm();
        }
        if (!lastDirectionRight) {
            spriteMain = spriteLeftStop;
        }
        else spriteMain = spriteRightStop;
    }
    if (velocityX > 0) {
        if (velocityX > runSpeedThreshold) {
            isFastRun = true;  // Set to fast run state
        }
        else {
            isFastRun = false; // Set to normal run state
        }
    }
    else {
        if (-velocityX > runSpeedThreshold) {
            isFastRun = true;  // Set to fast run state
        }
        else {
            isFastRun = false; // Set to normal run state
        }
    }


    if (isFastRun && !isBallForm) {
        // If moving right with fast run
        if (velocityX > 0) {
            spriteMain = spriteRightRun; // Switch to fast run sprite
        }
        // If moving left with fast run
        else if (velocityX < 0) {
            spriteMain = spriteLeftRun; // Switch to fast run sprite
        }
    }
    else if (isBallForm) {
        // If moving right in normal run
        if (velocityX > 0) {
            spriteMain = spriteRightBall;
        }
        // If moving left in normal run
        else if (velocityX < 0) {
            spriteMain = spriteLeftBall;
        }
    }
    else {
        // If moving right in normal run
        if (velocityX > 0) {
            spriteMain = spriteRight; // Use normal right run sprite
        }
        // If moving left in normal run
        else if (velocityX < 0) {
            spriteMain = spriteLeft; // Use normal left run sprite
        }
    }

    // 2) Jump
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && onGround) {
        velocityY = -20.0f;
        onGround = false;
    }
    else if (isFlying && sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        velocityY = -20.0f;
    }
    else if (isFlying && sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        velocityY = 20.0f;
    }

    // 3) Compute proposed new X position
    float newPosX = posX + velocityX;


    /////////////////////////////////////the Hitbox colllisions from left and right/////////////////////////////////////////////////////////
    // finding the hitbox edges
    float leftEdge = newPosX - 10;// this was done so that sonic can not get in the wall
    float rightEdge = newPosX + playerWidth + 20;

    float midY = posY;

    int rowMid = static_cast<int>(midY) / cell_size;
    int colLeft = static_cast<int>(leftEdge) / cell_size;
    int colRight = static_cast<int>(rightEdge) / cell_size;


    if (isFlying) {
        rowMid = static_cast<int>(midY + 25) / cell_size;

    }
    // Checking left or right side collisions
    bool collision = false;
    if (velocityX < 0) {
        // moving left: test left edge at top, mid, bottom
        if (lvl[rowMid][colLeft] == 'w' ||
            lvl[rowMid + 1][colLeft] == 'w')
        {
            collision = true;
        }
    }
    else if (velocityX > 0) {
        // moving right: test right edge
        if (lvl[rowMid][colRight] == 'w' ||
            lvl[rowMid + 1][colRight] == 'w')
        {
            collision = true;
        }
    }

    else if (velocityX < 0) {
        // moving left: test left edge at top, mid, bottom
        if (lvl[rowMid][colLeft] == 's' ||
            lvl[rowMid + 1][colLeft] == 's')
        {
            collision = true;
        }
    }

    else if (velocityX > 0) {
        // moving right: test right edge
        if (lvl[rowMid][colRight] == 's' ||
            lvl[rowMid + 1][colRight] == 's')
        {
            collision = true;
        }
    }


    //collision with breakable wALLS
    if (velocityX < 0) {
        // moving left: test left edge at top, mid, bottom
        if (lvl[rowMid][colLeft] == 'b' ||
            lvl[rowMid + 1][colLeft] == 'b')
        {
            collision = true;
        }
    }
    else if (velocityX > 0) {
        // moving right: test right edge
        if (lvl[rowMid][colRight] == 'b' ||
            lvl[rowMid + 1][colRight] == 'b')
        {
            collision = true;
        }
    }



    if (velocityX < 0) {
        // moving left: test left edge at top, mid, bottom
        if (lvl[rowMid][colLeft] == 'r' ||
            lvl[rowMid + 1][colLeft] == 'r')
        {
            lvl[rowMid][colLeft] = 'g'; // remove the ring from the map
            lvl[rowMid + 1][colLeft] = 'g';
            ringScore++;

            cout << "Rings: " << ringScore << endl;
        }
    }
    else if (velocityX > 0) {
        // moving right: test right edge
        if (lvl[rowMid][colRight] == 'r' ||
            lvl[rowMid + 1][colRight] == 'r')
        {
            lvl[rowMid][colRight] = 'g'; // remove the ring from the map
            lvl[rowMid + 1][colRight] = 'g';
            ringScore++;

            cout << "Rings: " << ringScore << endl;

        }
    }

    //bonus life

    if (velocityX < 0) {
        // moving left: test left edge at top, mid, bottom
        if (lvl[rowMid][colLeft] == 'l' ||
            lvl[rowMid + 1][colLeft] == 'l')
        {
            lvl[rowMid][colLeft] = 'g'; // remove the ring from the map
            lvl[rowMid + 1][colLeft] = 'g';
            health++;

            cout << "Health: " << health << endl;
        }
    }
    else if (velocityX > 0) {
        // moving right: test right edge
        if (lvl[rowMid][colRight] == 'l' ||
            lvl[rowMid + 1][colRight] == 'l')
        {
            lvl[rowMid][colRight] = 'g'; // remove the ring from the map
            lvl[rowMid + 1][colRight] = 'g';
            health++;

            cout << "Health: " << health << endl;

        }
    }



    //Resolve collision or apply movement
    if (!collision) {
        posX = newPosX;
    }
    else {
        // if collided, stop horizontal movement
        velocityX = 0;
    }

    // Back to normal form
    if (isBallForm && ballFormClock.getElapsedTime().asSeconds() >= ballDuration) {
        exitBallForm();
    }
}


void Player::player_gravity(char** lvl, float& offset_y, float cell_size, Clock& clk_spikes) {

    static bool platform_collision = false;

    // Step 1: Update offset_y with gravity velocity
    offset_y = posY + velocityY;
    char bottom_left_down = lvl[(int)((offset_y + playerHeight) / cell_size)][(int)((posX + playerWidth) / cell_size)]; ///changed this as it was causing problems, now it is sams as bottom right
    char bottom_right_down = lvl[(int)((offset_y + playerHeight) / cell_size)][(int)((posX + playerWidth) / cell_size)];
    char bottom_mid_down = lvl[(int)((offset_y + playerHeight) / cell_size)][(int)((posX + playerWidth / 2) / cell_size)];

    if (!isLead) {
        bottom_left_down = lvl[(int)((offset_y + playerHeight + 20) / cell_size)][(int)((posX) / cell_size)];
        bottom_right_down = lvl[(int)((offset_y + playerHeight + 20) / cell_size)][(int)((posX + playerWidth) / cell_size)];
        bottom_mid_down = lvl[(int)((offset_y + playerHeight + 20) / cell_size)][(int)((posX + playerWidth / 2) / cell_size)];
    }




    if (bottom_left_down == 'w' || bottom_mid_down == 'w' || bottom_right_down == 'w') {
        isLead ? platform_collision = false : platform_collision;
        onGround = true;
        velocityY = 0;

    }
    else if (isFlyingPowerUp) { // flying in powerup way
        onGround = true;
        posY = offset_y;
        velocityY += 0.5;
        if (velocityY >= terminalVelocity) velocityY = terminalVelocity;
    }
    else if (bottom_left_down == 'f' || bottom_mid_down == 'f' || bottom_right_down == 'f') {// check finish line
        isLead ? platform_collision = false : platform_collision;
        onGround = true;
        velocityY = 0;

    }
    else if (bottom_left_down == 'b' || bottom_mid_down == 'b' || bottom_right_down == 'b') {
        isLead ? platform_collision = false : platform_collision;
        onGround = true;
        velocityY = 0;

    }



    else if (bottom_left_down == 'p' || bottom_mid_down == 'p' || bottom_right_down == 'p') {

        if ((platform_collision == false) && (isLead)) {
            posY -= 64;
            platform_collision = true;

        }
        else {

            onGround = true;
            velocityY = 0;
        }


    }

    else if (bottom_left_down == 's' || bottom_mid_down == 's' || bottom_right_down == 's') {

        if ((clk_spikes.getElapsedTime().asSeconds() >= 1.0f) && (!isInvincible) && (isLead)) {
            health--;
            clk_spikes.restart();

            cout << "Player hit by spikes! Health: " << health << endl;
        }
        onGround = false;
        posY = offset_y;
        velocityY += gravity;
        if (velocityY >= terminalVelocity) velocityY = terminalVelocity;
    }

    else if ((bottom_left_down == 'x' || bottom_mid_down == 'x' || bottom_right_down == 'x') && (isLead)) { //for leading charachter game should end
        health = 0;
        return;
    }

    else if ((bottom_left_down == 'x' || bottom_mid_down == 'x' || bottom_right_down == 'x') && (!isLead)) { //for non-leading charachter game should NOT end
        platform_collision = false;
        onGround = true;
        velocityY = 0;
    }

    else
    {
        onGround = false;
        posY = offset_y;
        velocityY += gravity;
        if (velocityY >= terminalVelocity) velocityY = terminalVelocity;
    }



}

void Player::updateAnimation(float deltaTime = 0) {
    Animation::updateBallAnimation(
        spriteRightBall,
        spriteLeftBall,
        spriteMain,
        velocityX,
        isBallForm,
        leadIsFlying,
        ballFrameIndex,
        ballFrameTimer,
        ballFrameTime,
        ballFrameCount,
        ballFrameWidth,
        ballFrameHeight
    );

    Animation::updateLeftRightAnimation(
        spriteRight,
        spriteLeft,
        spriteMain,
        velocityX,
        isBallForm,
        leadIsFlying,
        leftRightFrameIndex,
        leftRightFrameTimer,
        leftRightFrameTime,
        leftRightFrameCount,
        leftRightFrameWidth,
        leftRightFrameHeight
    );

    Animation::updateLeftRightFastAnimation(
        spriteRightRun,
        spriteLeftRun,
        spriteMain,
        velocityX,
        isBallForm,
        isFastRun,
        leadIsFlying,
        leftRightFastFrameIndex,
        leftRightFastFrameTimer,
        leftRightFastFrameTime,
        leftRightFastFrameCount,
        leftRightFastFrameWidth,
        leftRightFastFrameHeight
    );
}


void Player::takeDamage() {
    health--;
}

void Player::enterBallForm() {
    if (ballCooldownActive) return; // prevent re-entry during cooldown

    isBallForm = true;
    ballCooldownActive = true;
    ballFormClock.restart(); // start the cooldown timer

    ballFrameIndex = 0;
    ballFrameTimer = 0.0f;

    if (velocityX > 0) {
        spriteRightBall.setTextureRect(sf::IntRect(ballFrameIndex * ballFrameWidth, 0, ballFrameWidth, ballFrameHeight));
        spriteMain = spriteRightBall;
    }
    else {
        spriteLeftBall.setTextureRect(sf::IntRect(ballFrameIndex * ballFrameWidth, 0, ballFrameWidth, ballFrameHeight));
        spriteMain = spriteLeftBall;
    }

    spriteMain.setScale(2.0f, 2.0f);
    currentHitbox = &hitboxBall;
    updateAnimation();
}

void Player::exitBallForm() {
    isBallForm = false;
    ballCooldownActive = false;

    if (velocityX > 0) {
        spriteMain = spriteRight;
    }
    else {
        spriteMain = spriteLeft;
    }

    spriteMain.setScale(2.5f, 2.5f);
    currentHitbox = &hitboxNormal;
}

void Player::rollAttack() {
    // TODO: Implement rolling attack
}

//void Player::checkCollisionWithMap(Map& map) {
//    // TODO: Handle map collision
//}
//
//void Player::checkCollisionWithCollectibles(Collectible* collectibles[], int count) {
//    // TODO: Handle collision with collectibles
//}
//
//void Player::checkCollisionWithEnemies(Enemy* enemies[], int count) {
//    // TODO: Handle collision with enemies
//}
//
//void Player::checkCollisionWithObstacles(Obstacle* obstacles[], int count) {
//    // TODO: Handle collision with obstacles
//}

void Player::draw(sf::RenderWindow& window, float offsetX) {
    if ((isFlying) || (isFlyingPowerUp)) {

        if (velocityX < 0) {
            flyingLeftSprite.setPosition(posX - offsetX, posY); // adjust only x-axis
            window.draw(flyingLeftSprite);
        }
        else {
            flyingRightSprite.setPosition(posX - offsetX, posY); // adjust only x-axis
            window.draw(flyingRightSprite);
        }
    }
    else {
        spriteMain.setPosition(posX - offsetX, posY); // adjust only x-axis
        window.draw(spriteMain);
    }
}
void Player::draw(sf::RenderWindow& window) {
    if ((isFlying) || (isFlyingPowerUp)) {
        if (velocityX < 0) {
            flyingLeftTexture.loadFromFile("Data/fly_together_left.png");
            //currentHitbox = new sf::FloatRect(posX, posY, 60, 12.5);
            flyingLeftSprite.setTexture(flyingLeftTexture);
            flyingLeftSprite.setScale(1, 0.5f);
            flyingLeftSprite.setPosition(posX, posY); // adjust only x-axis
            window.draw(flyingLeftSprite);
        }
        else {
            flyingRightTexture.loadFromFile("Data/fly_together_right.png");
            //currentHitbox = new sf::FloatRect(posX, posY, 60, 12.5);
            flyingRightSprite.setTexture(flyingRightTexture);
            flyingRightSprite.setScale(1, 0.5f);
            flyingRightSprite.setPosition(posX, posY); // adjust only x-axis
            window.draw(flyingRightSprite);
        }
    }
    else {
        //cout << "RUNNING" << endl;
        spriteMain.setPosition(posX, posY); // adjust only x-axis
        window.draw(spriteMain);
    }
}

// Getters
float Player::getPosX() const {
    return posX;
}

float Player::getPosY() const {
    return posY;
}

float Player::getVelocityX() const {
    return velocityX;
}

float Player::getVelocityY() const {
    return velocityY;
}

float Player::getTerminalVelocity() const {
    return terminalVelocity;
}

int Player::getHealth() const {
    return health;
}

bool Player::getonGround() const {
    return onGround;
}

bool Player::getIsFlying() const {
    return isFlying;
}

bool Player::getIsBallForm() const {
    return isBallForm;
}

sf::FloatRect Player::getCurrentHitbox() const {
    return *currentHitbox;
}

sf::Sprite Player::getSprite() const {
    return spriteMain;
}


// Setters
void Player::setPosX(float x) {
    posX = x;
}

void Player::setPosY(float y) {
    posY = y;
}

void Player::setVelocityX(float vx) {
    velocityX = vx;
}

void Player::setVelocityY(float vy) {
    velocityY = vy;
}

void Player::setHealth(int h) {
    health = h;
}

void Player::setOnGround(bool ground) {
    onGround = ground;
}

void Player::setIsFlying(bool flying) {
    isFlying = flying;
}

void Player::setIsBallForm(bool ballForm) {
    isBallForm = ballForm;
}

//////////////////////////////////////////




void Player::setAcceleration(float acc) {
    acceleration = acc;
}
float Player::getAcceleration() {
    return acceleration;
}

void Player::setDeacceleration(float dec) {
    deacceleration = dec;
}
float Player::getDeacceleration() {
    return deacceleration;
}
void Player::setGravity(float grav) {
    gravity = grav;
}
float Player::getGravity() {
    return gravity;
}

void Player::setTerminalVelocity(float tv) {
    terminalVelocity = tv;
}

bool Player::getIsFlyingPowerUp() {
    return isFlyingPowerUp;
}

void Player::setIsFlyingPowerUp(bool flyingPowerUp) {
    isFlyingPowerUp = flyingPowerUp;
}

bool Player::getIsInvincible() {
    return isInvincible;
}
void Player::setIsInvincible(bool invincible) {
    isInvincible = invincible;
}
//////////////////////////////////////////


