#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H



#include "Enemy.h"
#include"CrawlingEnemy.h"
#include "CrabMeat.h"
#include "MotoBug.h"
#include "BatBrain.h"
#include "BeeBot.h"
#include <SFML/Graphics.hpp>

class EnemyFactory
{
public:
	Enemy* createEnemy(const std::string& type, int xPos, int yPos);
};

#endif ENEMYFACTORY_H