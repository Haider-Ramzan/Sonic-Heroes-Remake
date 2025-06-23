
#ifndef COLLECTABLESFACTORY_H
#define COLLECTABLESFACTORY_H




#include "Rings.h"
#include "Collectables.h"
#include "BonusLife.h"
#include "PowerUp.h"
using namespace std;
class CollectablesFactory
{
public:
	Collectables* createCollectable(string type);

};

#endif COLLECTABLESFACTORY_H

