#include "BossLevel.h"

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

BossLevel::BossLevel(int screenWidth)
	: Level("4", "Data/bg_minecraft.png", screenWidth) {
	bossEnemy = BossEnemy();
}	
BossLevel::~BossLevel() {
	// Destructor
}

void BossLevel::run(sf::RenderWindow& window, int& ringScore) {
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


    ///some work
    player->setHealth(10);

    player->setAcceleration(0.2f);
    player->setDeacceleration(-1.0f);
    player->setGravity(0.8f);

    follower1 = nullptr;
	follower2 = nullptr;


    while (window.isOpen()) {
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
			window.close();
        }

        float deltaTime = deltaClock.restart().asSeconds();
        window.clear();

        bgSprite.setPosition(camera.getOffset() * 0.0005f, 0);
        window.draw(bgSprite);

        map.drawMap(window, collectableRing->getSprite(), collectableLife->getSprite());

        player->draw(window);
        bossEnemy.drawBoss(window);


        player->useAbility(map.getLevel(), offset_y, map.getCellSize());

        player->move(map.getLevel(), map.getCellSize(), map.getWidth(), map.getHeight(), ringScore);

		bossEnemy.moveBoss(map.getLevel(),   map.getCellSize(),   map.getWidth() *map.getCellSize(),   map.getHeight() * map.getCellSize()  , player); // these map width and height give number of cells so i am  multiplying by cell size which 64


        player->player_gravity(map.getLevel(), offset_y, map.getCellSize(), clk_spikes);

        player->updateAnimation(deltaTime);



        camera.update(player->getPosX(), player->getVelocityX(), player->getTerminalVelocity());

        // Update health and score text
        healthText.setString("Health  " + std::to_string(player->getHealth()));
        scoreText.setString("Score  " + std::to_string(ringScore));
        window.draw(healthText);
        window.draw(scoreText);
        //////////////////////

        if (player->getHealth() <= 0) {
            window.clear();
            return;
        }
        if (bossEnemy.getHealth() <= 0) {
            window.clear();
            return;
        }

        window.display();

		

    }


}

bool BossLevel::isWinner() {

	if (bossEnemy.getHealth() <= 0) {
		return true;
	}
	else {
		return false;
	}
}
