#include <SFML/Graphics.hpp>
#include "globals.h"
#include "Tank.h"
#include "Bullet.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
/*
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
sf::Texture mapTexture;
sf::Texture panelTexture;
sf::Texture welcomeScreenTexture;
sf::Texture battleButtonTexture;
sf::Texture restartButtonTexture;
sf::Texture addIconTexture;
sf::Texture minusIconTexture;

sf::RectangleShape map;
sf::RectangleShape panel;
sf::RectangleShape welcomeScreen;
sf::RectangleShape battleButton;
sf::RectangleShape restartButton;
sf::RectangleShape minusIcon;
sf::RectangleShape addIcon;


int generateRandomNumber(int min, int max) {
	int number = std::rand() % max + min;
	return number;
}

void loadTextures() {
    texture1.loadFromFile("health.png");
    texture2.loadFromFile("dmg.png");
    texture3.loadFromFile("speed.png");
    texture4.loadFromFile("bombAdd.png");
    boxTexture.loadFromFile("box.png");
    brickTexture.loadFromFile("bricks.png");
    wallTexture.loadFromFile("wall.png");
    bomb.loadFromFile("bomb.png");
    playerTexture.loadFromFile("player.png");
    playerTextureHitted.loadFromFile("playerHitted.png");
    enemyTexture.loadFromFile("enemy.png");
    enemyTextureHitted.loadFromFile("enemyHitted.png");
    mapTexture.loadFromFile("map.jpg");
    panelTexture.loadFromFile("panel.png");
    welcomeScreenTexture.loadFromFile("welcomeScreen.png");
    battleButtonTexture.loadFromFile("battleButton.png");
    restartButtonTexture.loadFromFile("restartButton.png");
    minusIconTexture.loadFromFile("minus.jpg");
    addIconTexture.loadFromFile("plus.jpg");


    map.setSize(sf::Vector2f(900, 800));
    map.setTexture(&mapTexture);

    panel.setSize(sf::Vector2f(200, 800));
    panel.setTexture(&panelTexture);
    panel.setPosition(900, 0);

    welcomeScreen.setSize(sf::Vector2f(500, 400));
    welcomeScreen.setTexture(&welcomeScreenTexture);
    welcomeScreen.setPosition(200, 200);

    battleButton.setSize(sf::Vector2f(120, 70));
    battleButton.setTexture(&battleButtonTexture);

    restartButton.setSize(sf::Vector2f(70, 70));
    restartButton.setTexture(&restartButtonTexture);
}
*/