#include "OptionsScreen.h"
#include <iostream>
using namespace std;


OptionsScreen :: OptionsScreen(sf::RenderWindow* window, int v) : Screen (window), volume(v){
	// Load background texture
	if (!bgTexture.loadFromFile("Data/bg_option.png")) {
		cout << "Error loading background texture!" << endl;
	}
	// Set background sprite
	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(0, 0);

	// Load font
	if (!font.loadFromFile("Data/bold.ttf")) {
		cout << "Error loading font!" << endl;
	}

}

void OptionsScreen::draw() {

	Text exitText, showText;

	

	//show text
	showText.setFont(font);
	showText.setString("Press Up or down to increase or decrease Volume");
	showText.setCharacterSize(24);
	showText.setFillColor(Color::White);
	showText.setPosition(200, 350);

	// Exit Option
	exitText.setFont(font);
	exitText.setString("Press B to go to Menu");
	exitText.setCharacterSize(36);
	exitText.setFillColor(Color::White);
	exitText.setPosition(400, 600);

	window->draw(bgSprite);
	window->draw(showText);
	window->draw(exitText);


}

OptionsScreen::~OptionsScreen() {

}

void OptionsScreen::setVolume(int v) {
	volume = v;
}

