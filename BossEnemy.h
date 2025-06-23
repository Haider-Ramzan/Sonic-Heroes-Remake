
#ifndef BOSSENEMY_H
#define BOSSENEMY_H




#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;

class BossEnemy
{
private:
	float PosX;
	float PosY;

	int health;
	Clock boss_clk;
	Clock playerAttack_clk; // clock so that attack happens every 1 second

	float playerPosX;
	float playerPosY;

	int bossWidth;
	int bossHeight;

	bool isAttack;

	bool isMovingDown;
	bool isMovingUp;
	bool isMovingRight;
	bool isMovingLeft;

	Texture rightTex;
	Texture leftTex;
	Sprite bossSprite;

public:

	BossEnemy();
	~BossEnemy();
	//setters and getters
	void setPosX(float x);
	float getPosX();
	void setPosY(float y);

	float getPosY();
	void setBossSprite(Sprite sprite);
		
	Sprite getBossSprite();
	void setRightTex(Texture texture);
	Texture getRightTex();
	void setLeftTex(Texture texture);
	Texture getLeftTex();

	void setHealth(int health);
	int getHealth();

	// functions

	void moveBoss(char ** lvl, int, int screenWidth, int screenHeight , Player*);

	void drawBoss(RenderWindow& window);


};

#endif BOSSENEMY_H

