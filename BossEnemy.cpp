#include "BossEnemy.h"


#include <iostream>
using namespace std;


BossEnemy::BossEnemy()
{
	bossHeight = 128;
	bossWidth = 128;

	PosX = 128;
	PosY = 128;
	health = 15;
	isMovingRight = true;
	isMovingLeft = false;
	isMovingDown = false;
	isMovingUp = false;
	isAttack = false;
	if (!rightTex.loadFromFile("Data/boss_right.png")) {
		cout << "Error loading right texture" << endl;
	}
	if (!leftTex.loadFromFile("Data/boss_left.png")) {
		cout << "Error loading left texture" << endl;
	}
	bossSprite.setTexture(rightTex);
	bossSprite.setPosition(PosX, PosY);
}

BossEnemy::~BossEnemy()
{
	// Destructor
}

/// workings

void BossEnemy::moveBoss(char** lvl, int cellSize, int screenWidth, int screenHeight, Player * player)
{
	if (boss_clk.getElapsedTime().asSeconds() > 10.0f) {
		boss_clk.restart();

		isAttack = true;
		isMovingDown = true;
		
		isMovingUp = false;
		isMovingRight = false;
		isMovingLeft = false;

		playerPosX = player->getPosX();
		playerPosY = player->getPosY();
	}

	if (isMovingDown) {
		float newPosY = PosY + 15.0f;
		if (newPosY >= playerPosY-32) {
			isMovingDown = false;

			if (PosX < playerPosX) {
				isMovingRight = true;
				isMovingLeft = false;
			}
			else if (PosX > playerPosX) {
				isMovingLeft = true;
				isMovingRight = false;
			}
		}
		else {
			PosY = newPosY;
		}
	}

	if (isMovingRight) {


		bossSprite.setTexture(rightTex);

		if (isAttack) {
			PosX += 15.0f;
			if (PosX >= playerPosX) {
				isAttack = false;
				isMovingRight = false;
				isMovingUp = true;
			}
		}

		else {
			PosX += 2.0f;

			if (PosX >= screenWidth - bossWidth - cellSize) { //to get best collision we need the boss man to move left when he touches the right wall. so minusing it's size and the block size
				isMovingRight = false;
				isMovingLeft = true;
			}
		}
		
	}
	
	else if (isMovingLeft) { //move either left or right

		bossSprite.setTexture(leftTex);

		if (isAttack) {
			PosX -= 15.0f;
			if (PosX <= playerPosX) {
				isAttack = false;
				isMovingRight = false;
				isMovingUp = true;
			}
		}

		else {
			bossSprite.setTexture(leftTex);
			PosX -= 2.0f;
			if (PosX <= cellSize) {
				isMovingRight = true;
				isMovingLeft = false;
			}
		}

		
	}

	if (isMovingUp) {

		float newPosY = PosY - 5.0f;
		if (newPosY <= cellSize + 64) {
			isMovingUp = false;
			isMovingRight = true;
			isAttack = false;

			
		}
		else {

			lvl[(int)(((playerPosY + 128) / cellSize))][(int)((playerPosX + 64 / 2.0) / cellSize)] = 'g'; //char bottom_mid_down = // 128 is the height 64 is the width of player
			PosY = newPosY;
		}
	}

	//attack only in ball form
	if (player->getIsBallForm()) {
		if (playerAttack_clk.getElapsedTime().asSeconds() > 1.0f) {
			
			if (player->getPosX() >= PosX && player->getPosX() <= PosX + bossWidth && player->getPosY() >= PosY && player->getPosY() <= PosY + bossHeight) {
				health--;
				playerAttack_clk.restart();
			}
		}
	}

	//if not in ball form and colllisions decrease player hp
	if (!player->getIsBallForm()) {
		if (playerAttack_clk.getElapsedTime().asSeconds() > 1.0f) {
			if (player->getPosX() >= PosX && player->getPosX() <= PosX + bossWidth && player->getPosY() >= PosY && player->getPosY() <= PosY + bossHeight) {
				player->setHealth(player->getHealth() - 1);
				playerAttack_clk.restart();
			}
		}
	}

}


void BossEnemy::drawBoss(RenderWindow& window)
{
	//show boss health at top right
	Font font;
	font.loadFromFile("Data/bold.ttf");
	Text healthText;
	healthText.setFont(font);
	healthText.setString("Boss Health: " + to_string(health));
	healthText.setCharacterSize(32);
	healthText.setFillColor(Color::White);
	healthText.setPosition(800,32 );

	// Draw the boss sprite
	bossSprite.setPosition(PosX, PosY);
	window.draw(bossSprite);
	window.draw(healthText);
}

void BossEnemy::setPosX(float x)
{
	PosX = x;
}

void BossEnemy::setPosY(float y)
{
	PosY = y;
}

float BossEnemy::getPosX()
{
	return PosX;
}

float BossEnemy::getPosY()
{
	return PosY;
}

void BossEnemy::setBossSprite(Sprite sprite)
{
	bossSprite = sprite;
}
Sprite BossEnemy::getBossSprite()
{
	return bossSprite;
}
void BossEnemy::setRightTex(Texture texture)
{
	rightTex = texture;
}
Texture BossEnemy::getRightTex()
{
	return rightTex;
}
	
void BossEnemy::setLeftTex(Texture texture)
{
	leftTex = texture;
}
Texture BossEnemy::getLeftTex()
{
	return leftTex;
}
void BossEnemy::setHealth(int health)
{
	this->health = health;
}
int BossEnemy::getHealth()
{
	return health;
}

