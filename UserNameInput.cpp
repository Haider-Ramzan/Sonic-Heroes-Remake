#include "UserNameInput.h"
#include <iostream>
using namespace std;
UserNameInput::UserNameInput(sf::RenderWindow* window) : Screen(window) {
    if (!font.loadFromFile("Data/KnightWarrior-w16n8.otf")) {
        cout << "Error loading font!" << endl;
    }

    promptText.setFont(font);
    promptText.setString("Enter your name: ");
    promptText.setCharacterSize(40);
    promptText.setFillColor(sf::Color::White);
    promptText.setPosition(100, 200);

    nameText.setFont(font);
    nameText.setCharacterSize(36);
    nameText.setFillColor(sf::Color::Green);
    nameText.setPosition(100, 300);
}

void UserNameInput::draw() {
    nameText.setString(currentInput);
    window->clear();
    window->draw(promptText);
    window->draw(nameText);
    window->display();
}

bool UserNameInput::handleInput(sf::Event& event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode == '\b' && !currentInput.empty()) {
            currentInput.pop_back();
        }
        else if (event.text.unicode == '\r' || event.text.unicode == '\n') {
            playerName = currentInput;
            return true;  // done entering
        }
        else if (event.text.unicode < 128 && currentInput.size() < 15) {
            currentInput += static_cast<char>(event.text.unicode);
        }
    }
    return false;
}

std::string UserNameInput::getPlayerName() const {
    return playerName;
}
