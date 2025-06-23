
#ifndef OPTIONSSCREEN_H
#define OPTIONSSCREEN_H



#include <SFML/Graphics.hpp>
#include "Screen.h"
class OptionsScreen : public Screen
{
private:
	Texture bgTexture;
	Sprite bgSprite;
	int volume;
public:
	OptionsScreen(sf::RenderWindow* window, int);
	void draw() override;
	void setVolume(int v);
	~OptionsScreen();

};
#endif OPTIONSSCREEN_H