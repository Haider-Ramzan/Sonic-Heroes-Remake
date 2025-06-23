
#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Map.h"
#include "SlidingWindow.h"
#include "Player.h"
#include "PlayerFactory.h"
#include "CollectablesFactory.h"

class Level {
protected:

    Map map;
    SlidingWindow camera;
    Player* player;
    Player* follower1;
    Player* follower2;
    PlayerFactory playerFactory;
    CollectablesFactory collectablesFactory;
    Collectables* collectableRing;
	Collectables* collectableLife;
	Collectables* collectablePowerUp;
    sf::Texture bgTexture;
    sf::Sprite bgSprite;

    float offset_y = 0.0f;

public:
    Level(const std::string& mapName, const std::string& bgPath, int screenWidth);
    virtual ~Level();
    virtual void run(sf::RenderWindow& window, int & ) = 0;
    virtual bool isWinner()=0;
    Player* getPlayer();
};
#endif LEVEL_H