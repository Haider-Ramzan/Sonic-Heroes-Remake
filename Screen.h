
#ifndef SCREEN_H
#define SCREEN_H



#include <SFML/Graphics.hpp>
using namespace sf;

class Screen {
protected:
    RenderWindow* window;
    Font font;

public:
    Screen(RenderWindow*);
    virtual void draw() = 0; // Pure virtual function
    virtual ~Screen();
};

#endif SCREEN_H
