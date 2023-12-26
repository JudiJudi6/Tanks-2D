#include "Global.h"
#include <iostream>

Global::Global(){}

sf::Vector2f Global::getRandomCordsForEnemySpawn() {
    int x, y;
    y = rand() % 751 + 25;

    if ((y >= 0 && y <= 60) || (y >= 740 && y <= 800)) {
        x = rand() % 851 + 25;
    }
    else {
        x = (rand() % 2 < 1) ? rand() % 40 + 25 : rand() % 46 + 830;
    }
    return sf::Vector2f(x, y);
}

sf::Vector2f Global::getRandomCordsForWalls() {
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

void Global::clearVectors() {
    walls.clear();
    bricks.clear();
    boxes.clear();
    enemyTanks.clear();
    enemyBullets.clear();
    availablePlace.clear();
    bonusEvents.clear();
    minesOnMap.clear();
}

void Global::loadTextures() {
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
}