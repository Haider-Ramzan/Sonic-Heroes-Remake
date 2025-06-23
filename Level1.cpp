#include "Level1.h"
#include <iostream>

using namespace sf;


Level1::Level1(int screenWidth)
    : Level("1", "Data/bg_minecraft.png", screenWidth) {

    //set level 1 accelerations and stuff
        //ADDED LINES OF CODE
    EnemyFactory L1;
    enemyCount = 4;
    enemyArray = new Enemy*[enemyCount];
    enemyArray[0] = L1.createEnemy("CrabMeat", 1342, 767);
    enemyArray[1] = (Motobug*)L1.createEnemy("MotoBug", 6339.5, 767);
    enemyArray[2] = (BatBrain*)L1.createEnemy("BatBrain", 6339.5, 500);
    enemyArray[3] = (BeeBot*)L1.createEnemy("BeeBot", 1342, 500);
    
    projectileCount = 0;

    for (int count = 0; count < enemyCount; ++count) {
        if (enemyArray[count]->getProjectileThrower()) {
            ++projectileCount;
        }
    }

    projectileArray = new Projectile*[projectileCount];

    int projectileIndex = 0;  // To keep track of the current index in the projectile array

    for (int count = 0; count < enemyCount; ++count) {
        if (enemyArray[count]->getProjectileThrower()) {
            // Create a new Projectile and store it in the array
            projectileArray[projectileIndex] = new Projectile(enemyArray[count]);
            ++projectileIndex;
        }
    }



}

void Level1::run(sf::RenderWindow& window, int & ringScore) {
    sf::Clock deltaClock;
    sf::Event ev;

    Clock clk_spikes;

    //show health and score
	sf::Font font;
	if (!font.loadFromFile("Data/arcade1.ttf")) {
		std::cout << "Error loading font" << std::endl;
	}
	sf::Text healthText;
	healthText.setFont(font);
	healthText.setCharacterSize(32);
	healthText.setFillColor(sf::Color::White);
	healthText.setPosition(10, 10);
    
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(32);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(10, 50);

	Text showInvinibility;
	showInvinibility.setFont(font);
	showInvinibility.setCharacterSize(32);
	showInvinibility.setFillColor(sf::Color::White);
	showInvinibility.setPosition(400, 10);
	showInvinibility.setString("Invincible!!!!");

	

    ///some work
	bool switchCharacter = false;
	player->setHealth(10);

    player->setAcceleration(0.2f);
    player->setDeacceleration(-1.0f);
    player->setGravity(1.0f);


    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            window.close();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
            switchCharacter = true;
        }
        if ((!(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))) && switchCharacter) {
            //float tempX = player->getPosX();
            //float tempY = player->getPosY();
            Player* Temp = player;
            player = follower1;
            follower1 = follower2;
            follower2 = Temp;

            player->setAcceleration(0.5f);
            player->setDeacceleration(-1.0f);
            player->setGravity(1.0f);
            //player->setPosX(tempX);
            //player->setPosY(tempY);
            switchCharacter = false;
        }

        float deltaTime = deltaClock.restart().asSeconds();
        window.clear();

        bgSprite.setPosition(camera.getOffset() * 0.0005f, 0);
        window.draw(bgSprite);

        
        //////////////////////

        map.drawMap(window, camera.getOffset(), collectableRing->getSprite(), collectableLife->getSprite(), collectablePowerUp->getSprite());



        ///////////////////////////


        player->useAbility(map.getLevel(), offset_y, map.getCellSize());
		player->usePowerUp(map.getLevel(), offset_y, map.getCellSize());

        player->draw(window, camera.getOffset());
        follower1->draw(window, camera.getOffset());
        follower2->draw(window, camera.getOffset());

        for (int i = 0; i < enemyCount; ++i) {
            if (enemyArray[i] != nullptr) {
                enemyArray[i]->update(map.getLevel(), map.getCellSize(), map.getWidth(), map.getHeight(), deltaTime, player);
                if (enemyArray[i]->getHealth() <= 0) {
                    ringScore += 100;
                    delete enemyArray[i];
                    enemyArray[i] = nullptr;
                }
            }
        }

        for (int projectileIndex = 0; projectileIndex < projectileCount; ++projectileIndex) {
            if (projectileArray[projectileIndex] != nullptr) {
                projectileArray[projectileIndex]->move(player, deltaClock, map.getLevel(), map.getWidth(), map.getHeight(), map.getCellSize());
            }
        }

        //////////////////////
        for (int i = 0; i < enemyCount; ++i) {
            if (enemyArray[i] != nullptr) {
                enemyArray[i]->draw(window, camera.getOffset());
            }
        }

        for (int projectileIndex = 0; projectileIndex < projectileCount; ++projectileIndex) {
            if (projectileArray[projectileIndex] != nullptr) {
                projectileArray[projectileIndex]->draw(window, camera.getOffset(), 0);
            }
        }



        player->move(map.getLevel(), map.getCellSize(), map.getWidth(), map.getHeight(), ringScore);
        follower1->followPlayer(player, map.getLevel(), map.getCellSize(), map.getWidth(), map.getHeight(), 100);
        follower2->followPlayer(player, map.getLevel(), map.getCellSize(), map.getWidth(), map.getHeight(), 170);

        player->player_gravity(map.getLevel(), offset_y, map.getCellSize(), clk_spikes);
        follower1->player_gravity(map.getLevel(), offset_y, map.getCellSize(), clk_spikes);
        follower2->player_gravity(map.getLevel(), offset_y, map.getCellSize(), clk_spikes);

        player->updateAnimation(deltaTime);
        follower1->updateAnimation(deltaTime);
        follower2->updateAnimation(deltaTime);


        camera.update(player->getPosX(), player->getVelocityX(), player->getTerminalVelocity());

		// Update health and score text
		healthText.setString("Health  " + std::to_string(player->getHealth()));
		scoreText.setString("Score  " + std::to_string(ringScore));
		window.draw(healthText);
		window.draw(scoreText);
        //////////////////////

		if (player->getIsInvincible()) {
			window.draw(showInvinibility);
		}

        if (player->getHealth() <= 0) {
			window.clear();
			return;
        }
        else if (player->getPosX() > 195 * 64) {
			window.clear();
			return;
        }

        window.display();
    }
}
 
bool Level1::isWinner() {
    if (player->getPosX() > 195 * 64) {
        return true;
    }

    return false;
}

Level1::~Level1() {
    for (int i = 0; i < enemyCount; ++i) {
        if (enemyArray[i] != nullptr) {
            delete enemyArray[i];
            enemyArray[i] = nullptr;
        }
    }
}
