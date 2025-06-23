
#ifndef GAME_H
#define GAME_H




#include <SFML/Graphics.hpp>
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "BossLevel.h"
#include "Level.h"
#include "MainMenu.h"
#include "Instruction.h"
#include "GameOverScoreScreen.h"
#include "MidScreen.h"
#include "WinScreen.h"
#include "LevelMenuScreen.h"
#include "OptionsScreen.h"

#include "Leaderboard.h"
#include "UserNameInput.h"

class Game{
	Level* level;
	Screen* screen;
public:
	Game();
	void run();
	~Game();

};

#endif GAME_H 
