
#ifndef FLYINGENEMY_H
#define FLYINGENEMY_H



#include "Enemy.h"
#include "Player.h"

class FlyingEnemy : public Enemy {
public:
    FlyingEnemy();
    virtual void move(char** lvl, int cellSize, int mapWidth, int mapHeight, Player* player) = 0;
    virtual void attack() = 0;
    virtual void takeDamage() = 0;
    virtual ~FlyingEnemy() {}
    virtual void update(char** lvl, int cellSize, int mapWidth, int mapHeight, float deltaTime, Player* player) = 0;

};

#endif FLYINGENEMY_H
