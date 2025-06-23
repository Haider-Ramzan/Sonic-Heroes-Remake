

#ifndef LEVEL1_H
#define LEVEL1_H

#include "Level.h"
#include "CrabMeat.h"
#include "Enemy.h"
#include "Motobug.h"
#include "BeeBot.h"
#include "EnemyFactory.h"
#include "Projectile.h"

class Level1 : public Level {

    //ADDED ATTRIBUTES
private:
    Enemy** enemyArray;
    int enemyCount;
    Projectile** projectileArray;
    int projectileCount;
public:
    Level1(int screenWidth);
    void run(sf::RenderWindow& window, int&); // virtual functons 
    bool isWinner();

    //ADDED A DESTRUCTOR
    ~Level1();
};
#endif LEVEL1_H

