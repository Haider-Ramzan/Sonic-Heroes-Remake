#ifndef COLLECTABLES_H
#define COLLECTABLES_H





#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Collectables {
protected:
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Collectables();
    virtual ~Collectables();

    bool setTexture(const std::string& filepath);
    void setPosition(float x, float y);

    sf::Sprite& getSprite();
    sf::Texture& getTexture();

};

#endif COLLECTABLES_H


