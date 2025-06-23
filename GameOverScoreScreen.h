#ifndef GAMEOVERSCORESCREEN_H
#define GAMEOVERSCORESCREEN_H


#include <SFML/Graphics.hpp>
#include "Screen.h"
class GameOverScoreScreen : public Screen {
private:
    Texture bgTexture;
    Sprite bgSprite;
    int score;
    std::string playerName;
public:
    GameOverScoreScreen(sf::RenderWindow* window, int score, const std::string& playerName);
    void draw() override;
    ~GameOverScoreScreen();
};

#endif GAMEOVERSCORESCREEN_H
