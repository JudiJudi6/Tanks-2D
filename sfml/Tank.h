#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.h"

class Tank {
private:
    sf::Texture texture; // tekstura
    sf::Texture textureHitted; //tekstura podczas trafienia
    sf::Clock hitClock; // zegar obs³uguj¹cy zmiane tekstury
    sf::Vector2f oldEnemyPosition = sf::Vector2f(0.0f, 0.0f); // poprzednia pozycja
    bool isHitted = false; // flaga trafieñ
    int newDirection = std::rand() % 4; // losowy kierunek jazdy
    int newDirectionChangeTime = std::rand() % 3000 + 500; // czas kiedy nastapi zmiana kierunku jazdy
    bool killed = false; // flaga obs³uguj¹ca zniszczenie czo³gu
    sf::Time killedTime; // czas zniszczenia pojazdu
    bool respawn = false; // respawn
    bool onMine = false; // flaga obs³uguj¹ca najechanie na minê

public:
    Tank(sf::Vector2f position, float speed, int flag);
    sf::RectangleShape body;
    sf::Vector2f direction = sf::Vector2f(10.0f, 0);
    int healthPoints;
    float speed;
    bool stopped;
    int damagePerShot = 100;
    int mines = 3;
    static int destroyedTanks;
    static int gameTime;
    static bool countTime;
    static sf::Clock gameTimeClock;
    void startGameTime();
    void countGameTime();
    void stopGameTime();

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
    void addKill();

}; 