#include "Instruction.h"



Instruction::Instruction(sf::RenderWindow* window) : Screen(window)
{
	// Load background texture
	if (!bgTexture.loadFromFile("Data/bg_instructions.png")) {
		cout << "Error loading background texture!" << endl;
	}

	// Load font
	if (!font.loadFromFile("Data/bold.ttf")) {
		cout << "Error loading font!" << endl;
	}

}

void Instruction::draw()
{
	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(0, 0);
	window->draw(bgSprite);


}
Instruction::~Instruction()
{
	// Destructor implementation (if needed)
}