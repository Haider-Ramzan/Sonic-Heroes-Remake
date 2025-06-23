#pragma once
#include "Enemy.h"

Enemy::Enemy() : posX(0), posY(0), health(1), velocityX(0), velocityY(0) {}

void Enemy::draw(sf::RenderWindow& window, float offsetX = 0) {
    sprite.setPosition(posX - offsetX, posY);
    window.draw(sprite);
}

void Enemy::setPos(float x, float y) {
    posX = x;
    posY = y;
}

void Enemy::setHealth(int h) {
    health = h;
}

void Enemy::setTexture(const std::string& texturePath) {
    texture.loadFromFile(texturePath);
    sprite.setTexture(texture);
}

float Enemy::getPosX() const {
    return posX;
}

float Enemy::getPosY() const {
    return posY;
}

int Enemy::getHealth() const {
    return health;
}

sf::Sprite Enemy::getSprite() const {
    return sprite;
}

bool Enemy::getProjectileThrower() const {
    return projectileThrower;
}
