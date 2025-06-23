
#ifndef BEEBOT_H
#define BEEBOT_H

#include "FlyingEnemy.h"
#include "Enemy.h"


class BeeBot : public FlyingEnemy {
private:
    float timeSinceLastCollision;
    float collisionCooldown;
    float speed = 1.0f;              // Horizontal speed
    float zigzagSpeed = 0.1f;        // Speed of sine wave oscillation
    float zigzagAmplitude = 20.0f;   // How high/low it goes
    float zigzagTimer = 0.0f;        // Time counter for sine wave
    bool movingRight = true;         // Direction flag
    float initialY;

public:
    BeeBot(float x, float y);

    // Called every frame
    void update(char** lvl, int cellSize, int mapWidth, int mapHeight, float deltaTime, Player* player);
    void move(char** lvl, int cellSize, int mapWidth, int mapHeight, Player* player) override;

    void attack() override;
    void takeDamage() override;
    ~BeeBot() override;
};

#endif BEEBOT_H