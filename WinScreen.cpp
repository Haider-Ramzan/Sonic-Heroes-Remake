#include "WinScreen.h"
#include <fstream>
#include <iostream>
using namespace std;
using namespace sf;


WinScreen::WinScreen(sf::RenderWindow* window, int score, const std::string& playerName)
    : Screen(window), score(score), playerName(playerName) {

    if (!bgTexture.loadFromFile("Data/win_screen.png"))
        cout << "Error loading background texture!" << endl;

    if (!font.loadFromFile("Data/bold.ttf"))
        cout << "Error loading font!" << endl;

    // Step 1: Read scores
    ifstream inFile("Data/HighScore.txt");
    string names[11];
    int scores[11];
    int count = 0;

    while (count < 11 && inFile >> names[count] >> scores[count]) {
        count++;
    }
    inFile.close();

    // Step 2: Add new score
    names[count] = playerName;
    scores[count] = score;
    count++;

    // Step 3: Sort
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (scores[j] < scores[j + 1]) {
                std::swap(scores[j], scores[j + 1]);
                std::swap(names[j], names[j + 1]);
            }
        }
    }

    // Step 4: Write top 5
    ofstream outFile("Data/HighScore.txt");
    for (int i = 0; i < count && i < 10; ++i) {
        outFile << names[i] << " " << scores[i] << "\n";
    }
    outFile.close();
}

void WinScreen::draw()
{
    Text scoreText, exitText;

    // Score Text
    scoreText.setFont(font);
    scoreText.setString("Your Score: " + to_string(score));
    scoreText.setCharacterSize(36);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(50, 50);
    // Exit Option
    exitText.setFont(font);
    exitText.setString("Press B to go to Menu");
    exitText.setCharacterSize(36);
    exitText.setFillColor(Color::White);
    exitText.setPosition(50, 150);
    // Draw everything

    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(0, 0);
    window->draw(bgSprite);
    window->draw(scoreText);
    window->draw(exitText);
}

WinScreen::~WinScreen() {}

