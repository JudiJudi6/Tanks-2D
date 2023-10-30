#ifndef ENEMYINTELLIGENCE
#define ENEMYINTELLIGENCE
#pragma once

#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Wall.h"
#include "Brick.h"
#include "Box.h"
#include <cstdlib>
#include <ctime>

extern std::vector<Wall> walls;
extern std::vector<Brick> bricks;
extern std::vector<Box> boxes;
extern std::vector<Tank> enemyTanks;
extern std::vector<Bullet> enemyBullets;
extern std::vector<sf::Vector2f> availablePlace;
/*
extern sf::Vector2f oldEnemyPosition;
//extern int newDirection;
//extern sf::Clock clock;

void enemyIntelligence(Tank &enemyTank, Tank &playerTank, Bullet& enemyBullet, sf::Clock &clock);
int generateRandomNumber(int min, int max);

*/
#endif // GLOBALS_H