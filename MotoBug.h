
#ifndef MOTOBUG_H
#define MOTOBUG_H

#include "CrawlingEnemy.h"
#include "Enemy.h"


class Motobug : public CrawlingEnemy {
private:
    bool movingRight;          // Direction flag
    float timeSinceLastCollision;
    float collisionCooldown;
    float speed;

public:
    Motobug(float x, float y);

    // Called every frame
    void update(char** lvl, int cellSize, int mapWidth, int mapHeight, float deltaTime, Player* player);
    void move(char** lvl, int cellSize, int mapWidth, int mapHeight, Player* player) override;

    void attack() override;
    void takeDamage() override;
    ~Motobug() override;
};
#endif MOTOBUG_H