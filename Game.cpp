#include "Game.h"

Game::Game() {
	
}

void Game::run() {
	//rings mean score +=1
	//small enemmies mean score += 100
	//boss means score += 1000

	Font font;
	if (!font.loadFromFile("Data/bold.ttf")) {
		cout << "Error loading font!" << endl;
	}


	const int screen_x = 1200;
	const int screen_y = 900;
	sf::RenderWindow window(sf::VideoMode(screen_x, screen_y), "Sonic the Hedgehog-OOP", sf::Style::Close);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(90);

	int totalScore = 0;

	level = new Level1(screen_x);
	screen = new MainMenu(&window);

	//music

	int volume = 30;
	sf::Music levelMusic;
	levelMusic.openFromFile("Data/GameMusic/StartMenu.mp3");
	levelMusic.setVolume(volume);
	levelMusic.setLoop(true);
	levelMusic.play();

	bool mainMenuScreen_flag = true;
	bool level1_flag = false;
	bool instruction_flag = false;
	bool level_menu_flag = false;
	bool options_flag = false;
	bool gameOver_flag = false;
	bool level2_flag = false;
	bool midScreen_1_2_flag = false;
	bool level3_flag = false;
	bool midScreen_2_3_flag = false;
	bool midScreen_3_boss_flag = false;
	bool winScreen_flag = false;
	bool bossLevel_flag = false;

	bool leaderboard_flag = false;
	UserNameInput* userInput = new UserNameInput(&window);
	bool nameEntered = false;
	string playerName;

	while (!nameEntered && window.isOpen()) {
		Event ev;
		while (window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				window.close();
				return;
			}
			nameEntered = userInput->handleInput(ev);
		}
		userInput->draw();
	}
	playerName = userInput->getPlayerName();
	delete userInput;




	while (window.isOpen()) {
		Event ev;

		while (mainMenuScreen_flag) {

			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed) {
					window.close();
					return;
				}


			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
				mainMenuScreen_flag = false;
				level = new Level1(screen_x);
				level1_flag = true;
				levelMusic.openFromFile("Data/GameMusic/Level1.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
				mainMenuScreen_flag = false;
				instruction_flag = true;
				delete screen;
				screen = new Instruction(&window);
				levelMusic.openFromFile("Data/GameMusic/StartMenu.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
				// Show instructions

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
				mainMenuScreen_flag = false;
				level_menu_flag = true;
				delete screen;
				screen = new LevelMenuScreen(&window);
				levelMusic.openFromFile("Data/GameMusic/StartMenu.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
				// Show levels
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				mainMenuScreen_flag = false;
				options_flag = true;
				delete screen;
				screen = new OptionsScreen(&window, volume);
				levelMusic.openFromFile("Data/GameMusic/StartMenu.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
				mainMenuScreen_flag = false;
				leaderboard_flag = true;
				delete screen;
				screen = new Leaderboard(&window);
				levelMusic.openFromFile("Data/GameMusic/StartMenu.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				window.close();
				return;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
				return;
			}
			window.clear();
			screen->draw();
			window.display();


		}

		while (leaderboard_flag) {
			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed)
					window.close();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
				leaderboard_flag = false;
				mainMenuScreen_flag = true;
				delete screen;
				screen = new MainMenu(&window);
				levelMusic.openFromFile("Data/GameMusic/StartMenu.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}

			screen->draw();
		}

		while (options_flag) {

			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed) {
					window.close();
					return;
				}
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				if (volume < 100) {
					volume++;
				}

			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				if (volume > 0) {
					volume--;
				}
				screen->draw();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
				options_flag = false;
				mainMenuScreen_flag = true;
				delete screen;
				screen = new MainMenu(&window);
				levelMusic.openFromFile("Data/GameMusic/StartMenu.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}

			Text volumeText;

			// Score Text
			volumeText.setFont(font);
			volumeText.setString("Volume: " + to_string(volume));
			volumeText.setCharacterSize(36);
			volumeText.setFillColor(Color::White);
			volumeText.setPosition(200, 300);

			levelMusic.setVolume(volume);
			window.clear();
			window.draw(volumeText);
			screen->draw();
			window.display();

		}

		while (level_menu_flag) {
			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed) {
					window.close();
					return;
				}


			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				totalScore = 0;
				level_menu_flag = false;
				level1_flag = true;
				delete level;
				level = new Level1(screen_x);
				levelMusic.openFromFile("Data/GameMusic/Level1.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
				
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
				totalScore = 0;
				level_menu_flag = false;
				level2_flag = true;
				delete level;
				level = new Level2(screen_x);
				levelMusic.openFromFile("Data/GameMusic/Level2.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
				totalScore = 0;
				level_menu_flag = false;
				level3_flag = true;
				delete level;
				level = new Level3(screen_x);
				levelMusic.openFromFile("Data/GameMusic/Level3.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				totalScore = 0;
				level_menu_flag = false;
				bossLevel_flag = true;
				delete level;
				level = new BossLevel(screen_x);
				levelMusic.openFromFile("Data/GameMusic/BossLevel.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
				
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
				level_menu_flag = false;
				mainMenuScreen_flag = true;
				delete screen;
				screen = new MainMenu(&window);
				levelMusic.openFromFile("Data/GameMusic/StartMenu.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}

			window.clear();
			screen->draw();
			window.display();

		}

		while (instruction_flag) {
			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed) {
					window.close();
					return;
				}

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
				instruction_flag = false;
				mainMenuScreen_flag = true;
				delete screen;
				screen = new MainMenu(&window);
				levelMusic.openFromFile("Data/GameMusic/StartMenu.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}
			window.clear();
			screen->draw();
			window.display();
		}

		while (gameOver_flag) {
			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed) {
					window.close();
					return;
				}

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
				gameOver_flag = false;
				mainMenuScreen_flag = true;
				delete screen;
				screen = new MainMenu(&window);
				levelMusic.openFromFile("Data/GameMusic/StartMenu.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}


			window.clear();
			screen->draw();
			window.display();
		}

		while (level1_flag) {

			totalScore = 0;

			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed)
					window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				level1_flag = false;
				mainMenuScreen_flag = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				window.close();
			}

			level->run(window, totalScore);

			if (level->getPlayer()->getHealth() <= 0) {
				level1_flag = false;
				gameOver_flag = true;
				delete screen;
				levelMusic.openFromFile("Data/GameMusic/DieMusic.mp3");
				screen = new GameOverScoreScreen(&window, totalScore, playerName);
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}

			else if (level->isWinner()) { // change screen type here // this check exists inside level1.cpp too and checks for last five blocks as in level 1 total blocks = 200
				level1_flag = false;
				midScreen_1_2_flag = true;
				delete level;
				level = 0;
				delete screen;
				screen = new MidScreen(&window);
				levelMusic.openFromFile("Data/GameMusic/LevelComplete.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}

		}

		while (midScreen_1_2_flag) {

			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed) {
					window.close();
					return;
				}

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				midScreen_1_2_flag = false;

				level2_flag = true;
				delete level;
				level = new Level2(screen_x);
				levelMusic.openFromFile("Data/GameMusic/Level2.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
				
			}

			window.clear();
			screen->draw();
			window.display();

		}

		while (level2_flag) {
			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed)
					window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				level1_flag = false;
				mainMenuScreen_flag = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				window.close();
			}

			level->run(window, totalScore);

			if (level->getPlayer()->getHealth() <= 0) {
				level2_flag = false;
				gameOver_flag = true;
				delete screen;
				screen = new GameOverScoreScreen(&window, totalScore, playerName);
				levelMusic.openFromFile("Data/GameMusic/DieMusic.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}

			else if (level->isWinner()) { // change screen type here // this check exists inside level1.cpp too and checks for last five blocks as in level 1 total blocks = 200
				level2_flag = false;
				midScreen_2_3_flag = true;
				delete screen;
				screen = new MidScreen(&window);
				levelMusic.openFromFile("Data/GameMusic/LevelComplete.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}


		}

		while (midScreen_2_3_flag) {

			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed) {
					window.close();
					return;
				}

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				midScreen_2_3_flag = false;

				level3_flag = true;
				delete level;
				level = new Level3(screen_x);
				levelMusic.openFromFile("Data/GameMusic/Level3.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();

			}

			window.clear();
			screen->draw();
			window.display();

		}


		while (level3_flag) {
			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed)
					window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				level1_flag = false;
				mainMenuScreen_flag = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				window.close();
			}

			level->run(window, totalScore);

			if (level->getPlayer()->getHealth() <= 0) {
				level3_flag = false;
				gameOver_flag = true;
				delete screen;
				screen = new GameOverScoreScreen(&window, totalScore, playerName);
				levelMusic.openFromFile("Data/GameMusic/DieMusic.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}

			else if (level->isWinner()) { // change screen type here // this check exists inside level1.cpp too and checks for last five blocks as in level 1 total blocks = 200
				level3_flag = false;
				midScreen_3_boss_flag = true;
				delete screen;
				screen = new MidScreen(&window);
				levelMusic.openFromFile("Data/GameMusic/LevelComplete.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}


		}

		while (midScreen_3_boss_flag) {

			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed) {
					window.close();
					return;
				}

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				midScreen_3_boss_flag = false;

				bossLevel_flag = true;
				delete level;
				level = new BossLevel(screen_x);
				levelMusic.openFromFile("Data/GameMusic/BossLevel.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
				
			}

			window.clear();
			screen->draw();
			window.display();

		}

		while (bossLevel_flag) {
			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed)
					window.close();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				bossLevel_flag = false;
				mainMenuScreen_flag = true;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
				window.close();
			}

			level->run(window, totalScore);

			if (level->getPlayer()->getHealth() <= 0) {
				bossLevel_flag = false;
				gameOver_flag = true;
				delete screen;
				screen = new GameOverScoreScreen(&window, totalScore, playerName);
				levelMusic.openFromFile("Data/GameMusic/DieMusic.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}

			else if (level->isWinner()) {
				totalScore += 1000;
				bossLevel_flag = false;
				winScreen_flag = true;
				delete screen;
				screen = new WinScreen(&window, totalScore, playerName);
				levelMusic.openFromFile("Data/GameMusic/WonGame.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}

		}




		while (winScreen_flag) {
			while (window.pollEvent(ev)) {
				if (ev.type == sf::Event::Closed) {
					window.close();
					return;
				}

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
				winScreen_flag = false;
				mainMenuScreen_flag = true;
				delete screen;
				screen = new MainMenu(&window);
				levelMusic.openFromFile("Data/GameMusic/StartMenu.mp3");
				levelMusic.setVolume(volume);
				levelMusic.setLoop(true);
				levelMusic.play();
			}


			window.clear();
			screen->draw();
			window.display();
		}


	}

}

Game::~Game() {

	if (level != 0)
		delete level;
	if (screen != 0)
		delete screen;

}