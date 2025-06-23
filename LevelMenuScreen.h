
#ifndef LEVELMENUSCREEN_H
#define LEVELMENUSCREEN_H

#include "Screen.h"

class LevelMenuScreen : public Screen
{
private:
	Texture bgTexture;
	Sprite bgSprite;
public:
	LevelMenuScreen(sf::RenderWindow* window);
	void draw() override;
	~LevelMenuScreen();
};
#endif LEVELMENUSCREEN_H

