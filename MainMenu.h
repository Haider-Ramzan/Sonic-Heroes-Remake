#ifndef MAINMENU_H
#define MAINMENU_H



#include <SFML/Graphics.hpp>
#include "Screen.h"
class MainMenu : public Screen
{
private:
	Texture bgTexture;
	Sprite bgSprite;
public:
	MainMenu(sf::RenderWindow* window);
	void draw() override;
	~MainMenu();

};

#endif MAINMENU_H

