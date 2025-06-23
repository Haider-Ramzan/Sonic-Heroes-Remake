#ifndef BOSSLEVEL_H
#define BOSSLEVEL_H


#include "Level.h"
#include "BossEnemy.h"

class BossLevel : public Level {

private:
	BossEnemy bossEnemy;

public:
    BossLevel(int screenWidth);
    void run(sf::RenderWindow& window, int&) override; // virtual functons 
    bool isWinner() override;
	
	~BossLevel();

};
#endif BOSSLEVEL_H