
#ifndef LEADERBOARD_H
#define LEADERBOARD_H



#include "Screen.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <string>
using namespace sf;
using namespace std;

class Leaderboard : public Screen {
private:
    Text title;
    Text scoreEntries[10];
    Text backText;

public:
    Leaderboard(RenderWindow* window);
    void draw() override;
};
#endif LEADERBOARD_H