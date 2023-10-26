#ifndef TANK_H
#define TANK_H
#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.h"
class Tank {
private:
    sf::Texture texture;
    sf::Texture textureHitted;
    sf::Clock hitClock;
    sf::Vector2f oldEnemyPosition = sf::Vector2f(0.0f, 0.0f);
    float speed;
    bool isHitted = false;
    bool initialDirection = false;
    //int destroyedTanks = 0;
    int newDirection = std::rand() % 4;
    int newDirectionChangeTime = std::rand() % 3000 + 500;

public:
    Tank(sf::Vector2f position, float speed, const std::string& texturePath, const std::string& texturePathHitted);
    sf::RectangleShape body;
    sf::Vector2f direction;
    int healthPoints;
    bool stopped;

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
    void drawTank(sf::RenderWindow& window);
    bool getStopped();
    int getRandomDirection(sf::Clock& clock);
    void setNewDirection(int newDirection);
    int getNewDirection();
    void enemyIntelligence(Tank& playerTank, Bullet& enemyBullet, sf::Clock& clock);
   // bool isInitial();
    //void setInitial(bool initial);
    //void addKill();
   // int getKills();
}; 

#undef TANK_H
#endif // TANK_H