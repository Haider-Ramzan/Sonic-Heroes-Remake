
#ifndef LEVEL2_H
#define LEVEL2_H



#include "Level.h"
#include "CrabMeat.h"
#include "Enemy.h"
#include "Motobug.h"
#include "BeeBot.h"
#include "EnemyFactory.h"
#include "Projectile.h"

class Level2 : public Level {

    //ADDED ATTRIBUTES
private:
    Enemy** enemyArray;
    int enemyCount;
    Projectile** projectileArray;
    int projectileCount;
public:
    Level2(int screenWidth);
    void run(sf::RenderWindow& window, int&); // virtual functons 
    bool isWinner();

    //ADDED A DESTRUCTOR
    ~Level2();
};
#endif LEVEL2_H