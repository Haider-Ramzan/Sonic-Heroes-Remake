#include "EnemyFactory.h"
#pragma once

Enemy* EnemyFactory::createEnemy(const std::string& type, int xPos, int yPos)
{
	if (type == "MotoBug")
	{
		return new Motobug(xPos, yPos);
	}
	else if (type == "CrabMeat")
	{
		return new CrabMeat(xPos, yPos);
	}
	else if (type == "BatBrain")
	{
		return new BatBrain(xPos, yPos);
	}
	else if (type == "BeeBot")
	{
		return new BeeBot(xPos, yPos);
	}
	// Add more enemy types here if needed
	return nullptr; // Return nullptr if the type is not recognized
}

