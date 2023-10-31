#ifndef TANK_H
#define TANK_H
#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "PlayerTank.h"
class Tank {
private:
    sf::Texture texture;
    sf::Texture textureHitted;
    sf::Clock hitClock;
    sf::Vector2f oldEnemyPosition = sf::Vector2f(0.0f, 0.0f);
    bool isHitted = false;
    int newDirection = std::rand() % 4;
    int newDirectionChangeTime = std::rand() % 3000 + 500;
    sf::Vector2f previousPosition;
    bool killed = false;
    sf::Time killedTime;
    bool respawn = false;
    bool onMine = false;

public:
    Tank(sf::Vector2f position, float speed, int flag);
    sf::RectangleShape body;
    sf::Vector2f direction = sf::Vector2f(10.0f, 0);
    int healthPoints;
    float speed;
    bool stopped;
    int damagePerShot = 100;
    int mines = 3;

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
    void setStopped(bool isStop);
    int getRandomDirection(sf::Clock& clock);
    void setNewDirection(int newDirection);
    int getNewDirection();
    void enemyIntelligence(Tank& playerTank, Bullet& enemyBullet, sf::Clock& clock);
    bool castRays(const sf::Vector2f& newPosition);
    bool isWallBetweenTanks(const Tank& playerTank);
    void respawnEnemy();
    void eventBonusIntersects();
    void mineIntersects();

    void setDamage(int dmg);
    int getDamage();
    void setSpeed(float speed);
    float getSpeed();
    void setAddMines();
    void useOneMine();
    int getMines();
    void setMines(int mines);
}; 

#undef TANK_H
#endif // TANK_H