

#ifndef WINSCREEN_H
#define WINSCREEN_H



#include "Screen.h"

class WinScreen : public Screen {
private:
    int score;
    std::string playerName;
    Texture bgTexture;
    Sprite bgSprite;
public:
    WinScreen(sf::RenderWindow* window, int score, const std::string& playerName);
    void draw() override;
    ~WinScreen();
};
#endif WINSCREEN_H

