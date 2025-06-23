
#ifndef CRAWLINGENEMY_H
#define CRAWLINGENEMY_H



#include "Enemy.h"
#include "Player.h"  // Ensure this is in both CrawlingEnemy.h and Enemy.h

class CrawlingEnemy : public Enemy {
public:
    CrawlingEnemy();
    virtual void move(char** lvl, int cellSize, int mapWidth, int mapHeight, Player* player) = 0;
    virtual void attack() = 0;
    virtual void takeDamage() = 0;
    virtual ~CrawlingEnemy() {}
    virtual void update(char** lvl, int cellSize, int mapWidth, int mapHeight, float deltaTime, Player* player) = 0;

};

#endif CRAWLINGENEMY_H
