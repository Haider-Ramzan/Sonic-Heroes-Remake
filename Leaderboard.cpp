#include "Leaderboard.h"

Leaderboard::Leaderboard(RenderWindow* window) : Screen(window) {
    if (!font.loadFromFile("Data/bold.ttf")) {
        cout << "Failed to load font" << endl;
    }

    title.setFont(font);
    title.setString("Top Scores");
    title.setCharacterSize(50);
    title.setFillColor(Color::Green);
    title.setPosition(window->getSize().x / 2 - 150, 50);

    backText.setFont(font);
    backText.setString("Press B to return");
    backText.setCharacterSize(25);
    backText.setFillColor(Color::White);
    backText.setPosition(window->getSize().x / 2 - 120, window->getSize().y - 80);

    // Load scores
    ifstream file("Data/HighScore.txt");
    string line;
    int count = 0;

    while (getline(file, line) && count < 10) {
        // Split into name and score (last space-separated token is score)
        int lastSpaceIndex = -1;
        for (int i = line.length() - 1; i >= 0; --i) {
            if (line[i] == ' ') {
                lastSpaceIndex = i;
                break;
            }
        }

        if (lastSpaceIndex != -1) {
            string name = line.substr(0, lastSpaceIndex);
            int score = atoi(line.substr(lastSpaceIndex + 1).c_str());

            string entry = to_string(count + 1) + ". " + name + ": " + to_string(score);
            scoreEntries[count].setFont(font);
            scoreEntries[count].setString(entry);
            scoreEntries[count].setCharacterSize(30);
            scoreEntries[count].setFillColor(Color::White);
            scoreEntries[count].setPosition(window->getSize().x / 2 - 150, 150 + count * 50);
            count++;
        }
    }

    file.close();
}
void Leaderboard::draw() {
    window->clear();
    window->draw(title);
    for (int i = 0; i < 10; ++i) {
        if (scoreEntries[i].getString().getSize() > 0) {
            window->draw(scoreEntries[i]);
        }
    }
    window->draw(backText);
    window->display();
}