
#ifndef MIDSCREEN_H
#define MIDSCREEN_H


#include <SFML/Graphics.hpp>
#include "Screen.h"
class MidScreen : public Screen
{
private:
	Texture bgTexture;
	Sprite bgSprite;
public:
	MidScreen(sf::RenderWindow* window);
	void draw() override;
	~MidScreen();
};

#endif MIDSCREEN_H

