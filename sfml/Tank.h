#ifndef TANK_H
#define TANK_H
#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Stats.h"
class Tank {
private:
    sf::Texture texture;
    sf::Texture textureHitted;
    sf::Clock hitClock;
    float speed;
    bool isHitted = false;

public:
    Tank(float x, float y, float speed, const std::string& texturePath, const std::string& texturePathHitted);
    sf::RectangleShape body;
    sf::Vector2f direction;
    int healthPoints;

    void moveLeft();
    void moveRight();
    void moveTop();
    void moveBottom();
    sf::Vector2f getBulletDirection();
    void getHitted(Bullet& playerBullet);
    int getHealthPoints();
    void enemyGetKilled();
    void setHealthPoints(int points);
    void getHittedAnimation();
}; 

#undef TANK_H
#endif // TANK_H