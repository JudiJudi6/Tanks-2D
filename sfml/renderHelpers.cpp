#include "renderHelpers.h"
#include <iostream>

std::vector<Wall> walls;
std::vector<Brick> bricks;
std::vector<Box> boxes;
std::vector<Tank> enemyTanks;
std::vector<Bullet> enemyBullets;
std::vector<sf::Vector2f> availablePlace;
std::vector<BonusEvent> bonusEvents;
std::vector<Mine> minesOnMap;

sf::Texture boxTexture;
sf::Texture bomb;
sf::Texture brickTexture;
sf::Texture wallTexture;
sf::Texture texture1;
sf::Texture texture2;
sf::Texture texture3;
sf::Texture texture4;
sf::Texture playerTexture;
sf::Texture playerTextureHitted;
sf::Texture enemyTexture;
sf::Texture enemyTextureHitted;

sf::Vector2f getRandomCordsForEnemySpawn() {
    int x, y;

    y = rand() % 751 + 25;


    if ((y >= 0 && y <= 60) || (y >= 740 && y <= 800)) {
        x = rand() % 851 + 25 ;
    } else {
        x = (rand() % 2 < 1) ? rand() % 40 + 25 : rand() % 46 + 830;
    }
    return sf::Vector2f(x, y);
}

sf::Vector2f getRandomCordsForWalls() {
    sf::Vector2f randomCords = availablePlace[rand() % availablePlace.size()];

    auto it = std::find(availablePlace.begin(), availablePlace.end(), randomCords);

    if (it != availablePlace.end()) {
        availablePlace.erase(it);
    }

    if (availablePlace.size() == 0) {
        std::cout << "nie";
    }

    return randomCords;
}

