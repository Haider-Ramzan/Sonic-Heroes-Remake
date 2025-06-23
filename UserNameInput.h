
#ifndef USERINPUTSCREEN_H
#define USERINPUTSCREEN_H



#include "Screen.h"
#include <string>

class UserNameInput : public Screen {
private:
    std::string playerName;
    sf::Text promptText;
    sf::Text nameText;
    std::string currentInput;

public:
    UserNameInput(sf::RenderWindow* window);
    void draw() override;
    bool handleInput(sf::Event& event);
    std::string getPlayerName() const;
};
#endif USERINPUTSCREEN_H