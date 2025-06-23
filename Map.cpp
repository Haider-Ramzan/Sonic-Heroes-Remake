#pragma once

#include "Map.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

using namespace std;

Map::Map(std :: string lvlNumber): lvl(nullptr), cellSize(0), height(0), width(0) {

    if (lvlNumber == "1") {

		cellSize = 64;
		height = 14;
		width = 200;


		lvl = new char* [height];
		for (int i = 0; i < height; i += 1)
		{
			lvl[i] = new char[width] {'\0'};
		}




		// the ground
		for (int i = 0; i < 200; i++) {
			lvl[13][i] = 'w';
		}
		
		//the most sided walls
		for (int i = 0; i < 14; i++) {
			lvl[i][0] = 'w';
		}


		for (int i = 0; i < 14; i++) {
			lvl[i][199] = 'w';
		}
		//celing
		for (int i = 0; i < 200; i++) {
			lvl[0][i] = 'w';
		}
		//finsh line

		for (int i = 194; i < 199; i++) {
			lvl[13][i] = 'f';
		}

		
		

		//making the map in middle

		for (int i = 5; i < 10; i++) {
			lvl[11][i] = 'r';
		}

		for (int i = 10; i < 20; i++) {
			lvl[12][i] = 'w';
		}
		for (int i = 11; i < 19; i++) {
			lvl[11][i] = 'w';
		}
		for (int i = 12; i < 18; i++) {
			lvl[10][i] = 'w';
		}

		for (int i = 3; i < 10; i++) {
			lvl[i][15] = 'b';
		}
		


		for (int i = 11; i <13 ; i++) {
			for (int j = 27; j < 30; j++) {
				lvl[i][j] = 'w';
			}

		}

		for (int i = 30; i < 34; i++) {
			lvl[12][i] = 's';
		}

		for (int i = 11; i < 13; i++) {
			for (int j = 34; j < 37; j++) {
				lvl[i][j] = 'w';
			}

		}
		for (int i = 37; i < 40; i++) {
			lvl[12][i] = 's';
		}


		for (int i = 11; i < 13; i++) {
			for (int j = 40; j < 43; j++) {
				lvl[i][j] = 'w';
			}

		}
		


		for (int i = 45; i < 80; i++) {
			lvl[12][i] = 'w';
		}
		for (int i = 46; i < 79; i++) {
			lvl[11][i] = 'w';
		}


		for (int i = 9; i < 11; i++) {
			for (int j = 48; j < 51; j++) {
				lvl[i][j] = 'w';
			}

		}
		for (int i = 51; i < 53; i++) {
			lvl[10][i] = 's';
		}


		for (int i = 9; i < 11; i++) {
			for (int j = 53; j < 56; j++) {
				lvl[i][j] = 'w';
			}

		}

		for (int i = 56; i < 58; i++) {
			lvl[10][i] = 's';
		}

		for (int i = 9; i < 11; i++) {
			for (int j = 58; j < 61; j++) {
				lvl[i][j] = 'w';
			}

		}

		for (int i = 61; i < 64; i++) {
			lvl[10][i] = 's';
		}

		for (int i = 9; i < 11; i++) {
			for (int j = 64; j < 67; j++) {
				lvl[i][j] = 'w';
			}

		}

		for (int i = 67; i < 70; i++) {
			lvl[10][i] = 's';
		}

		for (int i = 9; i < 11; i++) {
			for (int j = 70; j < 73; j++) {
				lvl[i][j] = 'w';
			}

		}

		for (int i = 82; i < 86; i++) {
			lvl[8][i] = 'r';
			lvl[10][i] = 'p';
		}

		lvl[8][84] = 'l';

		for (int i = 88; i < 92; i++) {
			lvl[7][i] = 'r';
			lvl[9][i] = 'p';
		}

		for (int i = 94; i < 98; i++) {
			lvl[6][i] = 'r';
			lvl[8][i] = 'p';
		}

		for (int i = 100; i < 104; i++) {
			lvl[6][i] = 'r';
			lvl[8][i] = 'p';
		}

		for (int i = 106; i < 109; i++) {
			lvl[6][i] = 'r';
			lvl[8][i] = 'p';
		}




		for (int i = 8; i < 13; i++) {
			for (int j = 110; j < 120; j++) {
				lvl[i][j] = 'w';
			}
		}

		for (int i = 11; i < 13; i++) { 
			lvl[i][109] = 'w';
		}


		
		for (int i = 156; i < 158; i++) {
			for (int j = 8; j < 14; j++) {
				lvl[j][i] = 'w';
			}
			
		}
		

		for (int i = 160; i < 165; i++) {
			lvl[12][i] = 'w';
		}
		for (int i = 161; i < 164; i++) {
			lvl[11][i] = 'w';
		}
		lvl[10][162] = 'w';

		lvl[8][162] = 'h';


		for (int i = 170; i < 172; i++) {
			lvl[12][i] = 's';
		}

		for (int i = 177; i < 179; i++) {
			lvl[12][i] = 's';
		}

		for (int i = 184; i < 186; i++) {
			lvl[12][i] = 's';
		}








		wallTex1.loadFromFile("Data/block_mine.png");
		wallSprite1.setTexture(wallTex1);
		platformTex.loadFromFile("Data/brick2.png");
		platformSprite.setTexture(platformTex);
		spikesTex.loadFromFile("Data/spike.png");
		spikesSprite.setTexture(spikesTex);
		breakWallTex.loadFromFile("Data/breakable_walls.png");
		breakWallSprite.setTexture(breakWallTex);
		FinishTex.loadFromFile("Data/finish_block.png");
		FinishSprite.setTexture(FinishTex);

    }

	else if (lvlNumber == "2") {

		cellSize = 64;
		height = 16; // height changed to 16 to acomodate bottom less pits
		width = 250;


		lvl = new char* [height];
		for (int i = 0; i < height; i += 1)
		{
			lvl[i] = new char[width] {'\0'};
		}

		wallTex1.loadFromFile("Data/ice_block.png");
		wallSprite1.setTexture(wallTex1);
		platformTex.loadFromFile("Data/brick2.png");
		platformSprite.setTexture(platformTex);
		spikesTex.loadFromFile("Data/spike.png");
		spikesSprite.setTexture(spikesTex);
		breakWallTex.loadFromFile("Data/breakable_walls.png");
		breakWallSprite.setTexture(breakWallTex);
		FinishTex.loadFromFile("Data/finish_block.png");
		FinishSprite.setTexture(FinishTex);
		bottomLessTex.loadFromFile("Data/pit_block.png");
		bottomLessSprite.setTexture(bottomLessTex);

		///making the map

		// the ground
		for (int i = 0; i < 250; i++) {
			lvl[13][i] = 'w';
		}

		//the most sided walls
		for (int i = 0; i < 14; i++) {
			lvl[i][0] = 'w';
		}


		for (int i = 0; i < 14; i++) {
			lvl[i][249] = 'w';
		}
		//celing
		for (int i = 0; i < 250; i++) {
			lvl[0][i] = 'w';
		}
		//finsh line

		for (int i = 244; i < 249; i++) {
			lvl[13][i] = 'f';
		}

		// Early ramp with rings and breakables
		for (int i = 5; i < 10; i++) {
			lvl[11][i] = 'r';
		}
		for (int i = 10; i < 20; i++) {
			lvl[12][i] = 'w';
		}

		// Rising stairs challenge
		for (int step = 0; step < 5; step++) {
			for (int j = 0; j < 3; j++) {
				lvl[12 - step][20 + step * 3 + j+1] = 'w';
			}
		}

		

		for (int i = 20; i < 40; i++) {
			lvl[12][i] = 's';
		}



		for (int i = 52; i < 58; i ++) {
			lvl[8][i] = 'r';

			lvl[10][i] = 'p';
		}

		// Floating ring platform zone
		for (int i = 65; i < 75; i++) {
			lvl[8][i] = 'r';
			lvl[10][i] = 'p';
		}

		// Tall block with breakable
		for (int i = 8; i < 13; i++) {
			lvl[i][85] = 'b';
		}
		lvl[7][85] = 'w';

		lvl[11][87] = 'h';

		// Double spike hurdles
		for (int i = 90; i < 93; i++) {
			lvl[12][i] = 's';
		}
		for (int i = 100; i < 103; i++) {
			lvl[12][i] = 's';
		}

		// Mid-air platform jump section
		for (int i = 105; i < 109; i++) {
			lvl[8][i] = 'r';
			lvl[10][i] = 'p';
		}

		for (int i = 110; i < 114; i++) {
			lvl[7][i] = 'r';
			lvl[9][i] = 'p';
		}
		for (int i = 118; i < 122; i++) {
			lvl[6][i] = 'r';
			lvl[8][i] = 'p';
		}
		for (int i = 126; i < 130; i++) {
			lvl[5][i] = 'r';
			lvl[7][i] = 'p';
		}
		for (int i = 134; i < 138; i++) {
			lvl[4][i] = 'r';
			lvl[6][i] = 'p';
		}

		// Bonus ring zone on staircase
		for (int step = 0; step < 4; step++) {
			lvl[11 - step][145 + step * 2] = 'r';
			lvl[13 - step][145 + step * 2] = 'w';
		}

		lvl[11][145] = 'l';
		

		// Trap + reward section
		for (int i = 181; i < 185; i++) {
			lvl[11][i] = 'p';
		}
		for (int i = 186; i < 189; i++) {
			lvl[11][i] = 'p';
		}
		for (int i = 180; i < 190; i++) {
			lvl[12][i] = 's';
		}
		for (int i = 182; i < 188; i++) {
			lvl[9][i] = 'r';
		}

		// Final platform gauntlet
		for (int i = 200; i < 205; i++) {
			lvl[9][i] = 'p';
		}
		for (int i = 210; i < 215; i++) {
			lvl[8][i] = 'p';
		}
		for (int i = 220; i < 225; i++) {
			lvl[7][i] = 'p';
		}
		

		// bottom less pit

		for (int i = 220; i < 234; i++) {
			lvl[13][i] = 'g';
		}
		for (int i = 220; i < 234; i++) {
			lvl[14][i] = 'x';
		}

		// Ending block platform
		for (int i = 238; i < 244; i++) {
			for (int j = 9; j < 13; j++) {
				lvl[j][i] = 'w';
			}
		}

	}
	else if (lvlNumber == "3") {
		cellSize = 64;
		height = 16; // height changed to 16 to acomodate bottom less pits
		width = 300;


		lvl = new char* [height];
		for (int i = 0; i < height; i += 1)
		{
			lvl[i] = new char[width] {'\0'};
		}

		wallTex1.loadFromFile("Data/block_metal.png");
		wallSprite1.setTexture(wallTex1);
		platformTex.loadFromFile("Data/brick2.png");
		platformSprite.setTexture(platformTex);
		spikesTex.loadFromFile("Data/spike.png");
		spikesSprite.setTexture(spikesTex);
		breakWallTex.loadFromFile("Data/breakable_walls.png");
		breakWallSprite.setTexture(breakWallTex);
		FinishTex.loadFromFile("Data/finish_block.png");
		FinishSprite.setTexture(FinishTex);
		bottomLessTex.loadFromFile("Data/pit_block.png");
		bottomLessSprite.setTexture(bottomLessTex);


		///making the map

		// the ground
		for (int i = 0; i < 300; i++) {
			lvl[13][i] = 'w';
		}

		//the most sided walls
		for (int i = 0; i < 14; i++) {
			lvl[i][0] = 'w';
		}


		for (int i = 0; i < 14; i++) {
			lvl[i][299] = 'w';
		}
		//celing
		for (int i = 0; i < 300; i++) {
			lvl[0][i] = 'w';
		}
		//finsh line

		for (int i = 294; i < 299; i++) {
			lvl[13][i] = 'f';
		}


		for (int i = 5; i < 10; i++) {
			lvl[11][i] = 'r';
		}

		for (int i = 10; i < 20; i++) {
			lvl[12][i] = 'w';
		}
		for (int i = 11; i < 19; i++) {
			lvl[11][i] = 'w';
		}
		for (int i = 12; i < 18; i++) {
			lvl[10][i] = 'w';
		}

		for (int i = 3; i < 10; i++) {
			lvl[i][15] = 'b';
		}



		for (int i = 11; i < 13; i++) {
			for (int j = 27; j < 30; j++) {
				lvl[i][j] = 'w';
			}

		}

		for (int i = 30; i < 34; i++) {
			lvl[12][i] = 's';
		}

		for (int i = 11; i < 13; i++) {
			for (int j = 34; j < 37; j++) {
				lvl[i][j] = 'w';
			}

		}
		for (int i = 37; i < 40; i++) {
			lvl[12][i] = 's';
		}


		for (int i = 11; i < 13; i++) {
			for (int j = 40; j < 43; j++) {
				lvl[i][j] = 'w';
			}

		}



		for (int i = 45; i < 80; i++) {
			lvl[12][i] = 'w';
		}
		for (int i = 46; i < 79; i++) {
			lvl[11][i] = 'w';
		}


		for (int i = 9; i < 11; i++) {
			for (int j = 48; j < 51; j++) {
				lvl[i][j] = 'w';
			}

		}
		for (int i = 51; i < 53; i++) {
			lvl[10][i] = 's';
		}

		// Double spike hurdles
		for (int i = 90; i < 93; i++) {
			lvl[12][i] = 's';
		}
		for (int i = 100; i < 103; i++) {
			lvl[12][i] = 's';
		}

		// Mid-air platform jump section
		for (int i = 105; i < 109; i++) {
			lvl[8][i] = 'r';
			lvl[10][i] = 'p';
		}

		lvl[8][107] = 'l';

		for (int i = 110; i < 114; i++) {
			lvl[7][i] = 'r';
			lvl[9][i] = 'p';
		}
		for (int i = 118; i < 122; i++) {
			lvl[6][i] = 'r';
			lvl[8][i] = 'p';
		}
		for (int i = 126; i < 130; i++) {
			lvl[5][i] = 'r';
			lvl[7][i] = 'p';
		}
		for (int i = 134; i < 138; i++) {
			lvl[4][i] = 'r';
			lvl[6][i] = 'p';
		}

		lvl[4][136] = 'h';

		// Bonus ring zone on staircase
		for (int step = 0; step < 4; step++) {
			lvl[9 - step][145 + step * 2] = 'r';
			lvl[11 - step][145 + step * 2] = 'w';
		}

		for (int i = 165; i < 170; i++) {
			lvl[13][i] = 'g';
		}
		for (int i = 165; i <170 ; i++) {
			lvl[14][i] = 'x';
		}

		// Ring bridge on top
		for (int i = 190; i < 210; i += 2) lvl[4][i] = 'r';
		for (int i = 190; i < 210; i++) lvl[6][i] = 'p';

		// Drop to spikes and wall
		for (int i = 215; i < 218; i++) lvl[12][i] = 's';
		for (int i = 9; i < 11; i++) lvl[i][220] = 'w';

		// Final climb section
		for (int step = 0; step < 5; step++) {
			lvl[12 - step][250 + step * 4] = 'w';
			lvl[10 - step][250 + step * 4] = 'r';
		}




	}

	else if (lvlNumber == "4") {

		cellSize = 64;
		height = 16; // height changed to 16 to acomodate bottom less pits
		width = 19;


		lvl = new char* [height];
		for (int i = 0; i < height; i += 1)
		{
			lvl[i] = new char[width] {'\0'};
		}

		wallTex1.loadFromFile("Data/block_mine.png");
		wallSprite1.setTexture(wallTex1);
		platformTex.loadFromFile("Data/brick2.png");
		platformSprite.setTexture(platformTex);
		spikesTex.loadFromFile("Data/spike.png");
		spikesSprite.setTexture(spikesTex);
		breakWallTex.loadFromFile("Data/breakable_walls.png");
		breakWallSprite.setTexture(breakWallTex);
		FinishTex.loadFromFile("Data/finish_block.png");
		FinishSprite.setTexture(FinishTex);


		///making the map

		// the double ground ground
		for (int i = 0; i < 19; i++) {
			lvl[13][i] = 'w';
		}


		//the most sided walls
		for (int i = 0; i < 14; i++) {
			lvl[i][0] = 'w';
		}


		for (int i = 0; i < 14; i++) {
			lvl[i][18] = 'w';
		}
		//celing
		for (int i = 0; i < 19; i++) {
			lvl[0][i] = 'w';
		}


		// platforms
		for (int i = 5; i < 8; i++) {
			lvl[10][i] = 'p';
		}
		for (int i = 11; i < 14; i++) {
			lvl[10][i] = 'p';
		}

		lvl[7][1] = 'l';
		lvl[9][1] = 'p';
		lvl[9][2] = 'p';

		lvl[7][17] = 'l';
		lvl[9][17] = 'p';
		lvl[9][16] = 'p';

		//the bottomless pit under ground
		for (int i = 0; i < 19; i++) {
			lvl[14][i] = 'x';
		}
		


	}


}
Map::~Map() {
	for (int i = 0; i < height; i++) {
		delete[] lvl[i];
	}
	delete[] lvl;
}

void Map::drawMap(sf::RenderWindow& window, float offsetX, Sprite& rings, Sprite & bonusLife, Sprite & powerUp) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (lvl[i][j] == 'w') {
				wallSprite1.setPosition(j * cellSize - offsetX, i * cellSize);
				window.draw(wallSprite1);
			}
			else if (lvl[i][j] == 'p') {
				platformSprite.setPosition(j * cellSize - offsetX, i * cellSize);
				window.draw(platformSprite);
			}
			else if (lvl[i][j] == 's') {
				spikesSprite.setPosition(j * cellSize - offsetX, i * cellSize);
				window.draw(spikesSprite);
			}
			else if (lvl[i][j] == 'r') {
				rings.setPosition(j * cellSize - offsetX, i * cellSize);
				window.draw(rings);
			}
			else if (lvl[i][j] == 'b') {
				breakWallSprite.setPosition(j * cellSize - offsetX, i * cellSize);
				window.draw(breakWallSprite);
			}
			else if (lvl[i][j] == 'f') {
				FinishSprite.setPosition(j * cellSize - offsetX, i * cellSize);
				window.draw(FinishSprite);
			}
			else if (lvl[i][j] == 'x') {
				bottomLessSprite.setPosition(j * cellSize - offsetX, i * cellSize);
				window.draw(bottomLessSprite);
			}
			else if (lvl[i][j] == 'l') {
				bonusLife.setPosition(j * cellSize - offsetX, i * cellSize);
				window.draw(bonusLife);
			}
			else if (lvl[i][j] == 'h') {
				powerUp.setPosition(j * cellSize - offsetX, i * cellSize);
				window.draw(powerUp);
			}
			else if (lvl[i][j] == 'g') {
				// Empty space, do nothing
			}

			else {
				// Handle unexpected characters if necessary
			}
			
		}
	}
}

void Map::drawMap(sf::RenderWindow& window, Sprite& rings, Sprite& bonusLife) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (lvl[i][j] == 'w') {
				wallSprite1.setPosition(j * cellSize, i * cellSize);
				window.draw(wallSprite1);
			}
			else if (lvl[i][j] == 'p') {
				platformSprite.setPosition(j * cellSize, i * cellSize);
				window.draw(platformSprite);
			}
			else if (lvl[i][j] == 's') {
				spikesSprite.setPosition(j * cellSize, i * cellSize);
				window.draw(spikesSprite);
			}
			else if (lvl[i][j] == 'r') {
				rings.setPosition(j * cellSize, i * cellSize);
				window.draw(rings);
			}
			else if (lvl[i][j] == 'b') {
				breakWallSprite.setPosition(j * cellSize, i * cellSize);
				window.draw(breakWallSprite);
			}
			else if (lvl[i][j] == 'f') {
				FinishSprite.setPosition(j * cellSize, i * cellSize);
				window.draw(FinishSprite);
			}
			else if (lvl[i][j] == 'x') {
				bottomLessSprite.setPosition(j * cellSize, i * cellSize);
				window.draw(bottomLessSprite);
			}
			else if (lvl[i][j] == 'l') {
				bonusLife.setPosition(j * cellSize, i * cellSize);
				window.draw(bonusLife);
			}
			else if (lvl[i][j] == 'g') {
				// Empty space, do nothing
			}
			else {
				// Handle unexpected characters if necessary
			}

		}
	}
}

// Getters
char** Map::getLevel() const { return lvl; }
int Map::getHeight() const { return height; }
int Map::getWidth() const { return width; }
int Map::getCellSize() const { return cellSize; }
sf::Texture& Map::getWallTexture() { return wallTex1; }
sf::Sprite& Map::getWallSprite() { return wallSprite1; }

// Setters
void Map::setLevel(char** newLvl) { lvl = newLvl; }
void Map::setHeight(int h) { height = h; }
void Map::setWidth(int w) { width = w; }
void Map::setCellSize(int cs) { cellSize = cs; }
void Map::setWallTexture(const sf::Texture& tex) {
    wallTex1 = tex;
    wallSprite1.setTexture(wallTex1);
}
void Map::setWallSprite(const sf::Sprite& spr) { wallSprite1 = spr; }



