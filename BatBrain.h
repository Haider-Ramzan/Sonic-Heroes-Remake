
#ifndef BATBRAIN_H
#define BATBRAIN_H

#include "FlyingEnemy.h"
#include "Enemy.h"


class BatBrain : public FlyingEnemy {
private:
    bool movingRight;          // Direction flag
    float timeSinceLastCollision;
    float collisionCooldown;
    float speed;

public:
    BatBrain(float x, float y);

    // Called every frame
    void update(char** lvl, int cellSize, int mapWidth, int mapHeight, float deltaTime, Player* player);
    void move(char** lvl, int cellSize, int mapWidth, int mapHeight, Player* player) override;

    void attack() override;
    void takeDamage() override;
    ~BatBrain() override;
};

#endif BATBRAIN_H