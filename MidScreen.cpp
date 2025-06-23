#include "MidScreen.h"
#include <iostream>
using namespace std;


MidScreen::MidScreen(sf::RenderWindow* window) : Screen(window)
{
	// Load background texture
	if (!bgTexture.loadFromFile("Data/mid_screen.png")) {
		cout << "Error loading background texture!" << endl;
	}
	// Load font
	if (!font.loadFromFile("Data/bold.ttf")) {
		cout << "Error loading font!" << endl;
	}

}

void MidScreen::draw()
{
	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(0, 0);
	window->draw(bgSprite);


}

MidScreen::~MidScreen()
{
	// Destructor implementation (if needed)
}