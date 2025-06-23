#include "Level.h"


// Level.cpp
#include "Level.h"

Level::Level(const std::string& mapName, const std::string& bgPath, int screenWidth)
    : map(mapName), camera(screenWidth, 0) {


    // Load background
    bgTexture.loadFromFile(bgPath);
    bgSprite.setTexture(bgTexture);

    // Create player and followers
    player = playerFactory.createPlayer("Sonic");
    follower1 = playerFactory.createPlayer("Knuckles");
    follower2 = playerFactory.createPlayer("Tails");

    player->setPosX(250); player->setPosY(100);
    follower1->setPosX(100); follower1->setPosY(100);
    follower2->setPosX(100); follower2->setPosY(100);

    // Collectables
    collectableRing = collectablesFactory.createCollectable("Rings");
	collectableLife = collectablesFactory.createCollectable("BonusLife");
	collectablePowerUp = collectablesFactory.createCollectable("PowerUp");

}

Level::~Level() {
    delete player;
    delete follower1;
    delete follower2;
    delete collectableRing;
}

Player* Level::getPlayer() {
	return player;
}

