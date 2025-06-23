#include "LevelMenuScreen.h"

#include <iostream>
using namespace std;

LevelMenuScreen::LevelMenuScreen(sf::RenderWindow* window) : Screen(window)
{
	// Load background texture
	if (!bgTexture.loadFromFile("Data/levelMenuScreen.png")) {
		std::cout << "Error loading background texture!" << std::endl;
	}
	// Load font
	if (!font.loadFromFile("Data/bold.ttf")) {
		std::cout << "Error loading font!" << std::endl;
	}
}
void LevelMenuScreen::draw()
{
	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(0, 0);
	window->draw(bgSprite);
}

LevelMenuScreen::~LevelMenuScreen() {}