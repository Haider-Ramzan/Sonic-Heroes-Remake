
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include<iostream>
using namespace sf;
using namespace std;

class Instruction : public Screen
{
private:
	Texture bgTexture;
	Sprite bgSprite;
public:
	Instruction(sf::RenderWindow* window);
	void draw() override;
	~Instruction();

};

#endif INSTRUCTION_H

