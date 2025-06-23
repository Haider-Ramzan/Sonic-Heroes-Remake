#include "MainMenu.h"

#include <iostream>

using namespace sf;
using namespace std;


MainMenu::MainMenu(sf::RenderWindow* window) : Screen(window)
{
	// Load background texture
	if (!bgTexture.loadFromFile("Data/main_bg.png")) {
		cout << "Error loading background texture!" << endl;
	}

	// Load font
	if (!font.loadFromFile("Data/bold.ttf")) {
		cout << "Error loading font!" << endl;
	}
	
}

void MainMenu::draw()
{

	Text optionText;

	optionText.setFont(font);
	optionText.setString("Press R for options");
	optionText.setCharacterSize(24);
	optionText.setFillColor(Color::White);
	optionText.setPosition(10, 10);


	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(0, 0);
	window->draw(bgSprite);
	window->draw(optionText);
   
}
MainMenu::~MainMenu()
{
	// Destructor implementation (if needed)
}