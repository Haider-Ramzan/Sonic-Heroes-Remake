
#ifndef CRABMEAT_H
#define CRABMEAT_H



#include "CrawlingEnemy.h"
#include "Enemy.h"
class CrabMeat : public CrawlingEnemy {
private:
    bool movingRight;          // Direction flag
    float shootCooldown;       // Time between shots
    float timeSinceLastShot;   // Time since last shot
    float timeSinceLastCollision;
    float collisionCooldown;

public:
    CrabMeat(float x, float y);
    // Movement and behavior
    void shootProjectiles();

    // Called every frame
    void update(char** lvl, int cellSize, int mapWidth, int mapHeight, float deltaTime, Player* player);
    void move(char** lvl, int cellSize, int mapWidth, int mapHeight, Player* player) override;

    void attack() override;
    void takeDamage() override;
    ~CrabMeat() override;
};

#endif CRABMEAT_H
