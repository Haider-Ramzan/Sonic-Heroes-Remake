
#ifndef PLAYER_H
#define PLAYER_H



#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"
using namespace std;

using namespace sf;


class Player {

private:

protected:
    static int health;
    float posX;
    float posY;
    float velocityX; //all three follow each other
    float velocityY;
    float acceleration;
    float deacceleration;
    float terminalVelocity;
    float gravity;
    int playerHeight;
    int playerWidth;

    bool onGround;
    bool isFlying;
    bool isBallForm;
    bool isFastRun;
    bool lastDirectionRight;
    bool isLead;
    bool leadIsFlying;
    bool isInvincible = false; // Flag to check if the player is invincible
    bool isFlyingPowerUp = false; // Flag to check if the player is flying powerup

    sf::FloatRect hitboxNormal;
    sf::FloatRect hitboxBall;
    sf::FloatRect* currentHitbox;
    sf::FloatRect hitboxFlying;

    sf::Texture transparentTexture;
    sf::Texture ballLeftTexture;
    sf::Texture ballRightTexture;
    sf::Texture leftTexture;
    sf::Texture rightTexture;
    sf::Texture leftFastTexture;
    sf::Texture rightFastTexture;
    sf::Texture leftStopTexture;
    sf::Texture rightStopTexture;
    sf::Sprite spriteLeft;
    sf::Sprite spriteRight;
    sf::Sprite spriteLeftBall;
    sf::Sprite spriteRightBall;
    sf::Sprite spriteMain;
    sf::Sprite spriteLeftStop;
    sf::Sprite spriteRightStop;
    sf::Sprite spriteRightRun;
    sf::Sprite spriteLeftRun;
    sf::Sprite transparentSprite;
    sf::Sprite flyingLeftSprite;
    sf::Texture flyingLeftTexture;
    sf::Sprite flyingRightSprite;
    sf::Texture flyingRightTexture;

    //Ball time
    sf::Clock ballFormClock;     // Starts timing when ball form is entered
    bool ballCooldownActive = false;  // Prevents re-entering during cooldown
    float ballDuration = 6.0f;   // Duration to stay in ball form (in seconds)


    //Animation Additions

// Ball animation
    int ballFrameIndex;
    int ballFrameWidth;
    int ballFrameHeight;
    int ballFrameCount;
    float ballFrameTime;
    float ballFrameTimer;

    // Jog animation
    float leftRightFrameTimer;
    int leftRightFrameIndex;
    float leftRightFrameTime;
    int leftRightFrameCount;
    int leftRightFrameWidth;
    int leftRightFrameHeight;

    // Fast run animation
    float runSpeedThreshold;
    float leftRightFastFrameTimer;
    int leftRightFastFrameIndex;
    float leftRightFastFrameTime;
    int leftRightFastFrameCount;
    int leftRightFastFrameWidth;
    int leftRightFastFrameHeight;



public:
    // Constructor

    // Movement
    void move(char** lvl, float cell_size, int levelWidth, int levelHeight, int&);
    void followPlayer(Player* leadPlayer, char** lvl, float cell_size, int levelWidth, int levelHeight, int difference);

    virtual void player_gravity(char**, float&, float, Clock&);

    // Status
    void takeDamage();
    void enterBallForm();
    void exitBallForm();
    void rollAttack();

    // Collision checks
    /*void checkCollisionWithMap(Map& map);
    void checkCollisionWithCollectibles(Collectible* collectibles[], int count);
    void checkCollisionWithEnemies(Enemy* enemies[], int count);
    void checkCollisionWithObstacles(Obstacle* obstacles[], int count);*/

    // Drawing
    void draw(sf::RenderWindow& window, float);
    void draw(RenderWindow& window);

    //Animation
    void updateAnimation(float deltaTime);

    // Getters
    float getPosX() const;
    float getPosY() const;
    float getVelocityX() const;
    float getTerminalVelocity() const;
    float getVelocityY() const;
    int getHealth() const;
    bool getonGround() const;
    bool getIsFlying() const;
    bool getIsBallForm() const;
    sf::FloatRect getCurrentHitbox() const;
    sf::Sprite getSprite() const;

    // Setters
    void setPosX(float x);
    void setPosY(float y);
    void setVelocityX(float vx);
    void setVelocityY(float vy);
    void setHealth(int h);
    void setOnGround(bool ground);
    void setIsFlying(bool flying);

    float getAcceleration(); // add when abdullah sends
    void setAcceleration(float acc); //
    void setDeacceleration(float dec);
    float getDeacceleration();
    void setGravity(float grav);
    float getGravity();
    void setTerminalVelocity(float tv);

    void setIsFlyingPowerUp(bool flyingPowerUp);
    bool getIsFlyingPowerUp();

    void setIsInvincible(bool invincible);
    bool getIsInvincible();

    void setIsBallForm(bool ballForm);
    virtual void useAbility(char** lvl, float& offset_y, float cell_size) = 0;
    virtual void usePowerUp(char** lvl, float& offset_y, float cell_size) = 0;
};

#endif PLAYER_H





/// //////////////////////////////////////



/// ////////////////////////////////////////////


