#include "GameOverScoreScreen.h"
#include <fstream>
#include <iostream>

using namespace sf;
using namespace std;
GameOverScoreScreen::GameOverScoreScreen(sf::RenderWindow* window, int score, const std::string& playerName)
    : Screen(window), score(score), playerName(playerName) {

    if (!bgTexture.loadFromFile("Data/bg_gameover.png"))
        cout << "Error loading background texture!" << endl;

    bgSprite.setTexture(bgTexture);
    bgSprite.setPosition(0, 0);

    if (!font.loadFromFile("Data/bold.ttf"))
        cout << "Error loading font!" << endl;

    // Step 1: Read existing scores
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

    // Step 3: Sort descending (simple bubble sort)
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (scores[j] < scores[j + 1]) {
                std::swap(scores[j], scores[j + 1]);
                std::swap(names[j], names[j + 1]);
            }
        }
    }

    // Step 4: Write back top 5
    ofstream outFile("Data/HighScore.txt");
    for (int i = 0; i < count && i < 10; ++i) {
        outFile << names[i] << " " << scores[i] << "\n";
    }
    outFile.close();
}

void GameOverScoreScreen::draw()
{
    Text scoreText, exitText;

    // Score Text
    scoreText.setFont(font);
    scoreText.setString("Your Score: " + to_string(score));
    scoreText.setCharacterSize(36);
    scoreText.setFillColor(Color::White);
    scoreText.setPosition(200, 200);
    // Exit Option
    exitText.setFont(font);
    exitText.setString("Press B to go to Menu");
    exitText.setCharacterSize(36);
    exitText.setFillColor(Color::White);
    exitText.setPosition(200, 300);
    // Draw everything

    window->draw(bgSprite);
    window->draw(scoreText);
    window->draw(exitText);
}

GameOverScoreScreen::~GameOverScoreScreen()
{
    // Destructor implementation (if needed)
}