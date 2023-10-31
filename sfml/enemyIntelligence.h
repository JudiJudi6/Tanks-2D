#ifndef ENEMYINTELLIGENCE
#define ENEMYINTELLIGENCE
#pragma once

#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Wall.h"
#include "Brick.h"
#include "Box.h"
#include <cstdlib>
#include "BonusEvent.h"
#include "Mine.h"
#include <ctime>

extern std::vector<Wall> walls;
extern std::vector<Brick> bricks;
extern std::vector<Box> boxes;
extern std::vector<Tank> enemyTanks;
extern std::vector<Bullet> enemyBullets;
extern std::vector<sf::Vector2f> availablePlace;
extern std::vector<BonusEvent> bonusEvents;
extern std::vector<Mine> minesOnMap;

extern sf::Texture texture1;
extern sf::Texture texture2;
extern sf::Texture texture3;
extern sf::Texture texture4;
extern sf::Texture boxTexture;
extern sf::Texture brickTexture; 
extern sf::Texture wallTexture;
extern sf::Texture bomb;
extern sf::Texture playerTexture;
extern sf::Texture playerTextureHitted;
extern sf::Texture enemyTexture;
extern sf::Texture enemyTextureHitted;

#endif