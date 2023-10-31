#include "renderHelpers.h"
#include "enemyIntelligence.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

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

