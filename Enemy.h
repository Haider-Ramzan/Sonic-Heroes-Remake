
#ifndef ENEMY_H
#define ENEMY_H



#include <SFML/Graphics.hpp>
#include "Player.h"

class Enemy {
protected:
    float posX;
    float posY;
    float velocityX;
    float velocityY;
    int health;
    sf::Texture texture;
    sf::Sprite sprite;
    bool projectileThrower = false;//jo maarty hain, unhi ko true karun ga

public:
    Enemy();
    virtual ~Enemy() {}

    virtual void move(char** lvl, int cellSize, int mapWidth, int mapHeight, Player* player) = 0;
    virtual void attack() = 0;
    virtual void takeDamage() = 0;
    virtual void update(char** lvl, int cellSize, int mapWidth, int mapHeight, float deltaTime, Player* player) = 0;
    void draw(sf::RenderWindow& window, float offsetX);
    // Setters
    void setPos(float x, float y);
    void setHealth(int h);
    void setTexture(const std::string& texturePath);

    // Getters
    float getPosX() const;
    float getPosY() const;
    int getHealth() const;
    bool getProjectileThrower() const;
    sf::Sprite getSprite() const;
};

#endif ENEMY_H
