#include <SFML/Graphics.hpp>
#include "globals.h"
#include "Tank.h"
#include "Bullet.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include "Wall.h"
#include "Brick.h"	
#include "Box.h"
#include "Mine.h"

std::vector<Wall> walls;
std::vector<Brick> bricks;
std::vector<Box> boxes;
std::vector<Tank> enemyTanks;
std::vector<Bullet> enemyBullets;
std::vector<sf::Vector2f> availablePlace;
std::vector<BonusEvent> bonusEvents;
std::vector<Mine> minesOnMap;

sf::Texture texture1;
sf::Texture texture2;
sf::Texture texture3;
sf::Texture texture4;
sf::Texture boxTexture;
sf::Texture brickTexture;
sf::Texture wallTexture;
sf::Texture bomb;
sf::Texture playerTexture;
sf::Texture playerTextureHitted;
sf::Texture enemyTexture;
sf::Texture enemyTextureHitted;


int generateRandomNumber(int min, int max) {
	int number = std::rand() % max + min;
	return number;
}