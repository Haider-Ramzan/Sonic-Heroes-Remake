
#ifndef LEVEL3_H
#define LEVEL3_H


#include "Level.h"
#include "CrabMeat.h"
#include "Enemy.h"
#include "Motobug.h"
#include "BeeBot.h"
#include "EnemyFactory.h"
#include "Projectile.h"

class Level3 : public Level {

    //ADDED ATTRIBUTES
private:
    Enemy** enemyArray;
    int enemyCount;
    Projectile** projectileArray;
    int projectileCount;
public:
    Level3(int screenWidth);
    void run(sf::RenderWindow& window, int&); // virtual functons 
    bool isWinner();

    //ADDED A DESTRUCTOR
    ~Level3();
};
#endif LEVEL3_H