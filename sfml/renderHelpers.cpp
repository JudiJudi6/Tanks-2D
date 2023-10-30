#include "renderHelpers.h"
#include "enemyIntelligence.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

sf::Vector2f getRandomCordsForEnemySpawn() {
    int x, y;

    y = rand() % 751 + 25; // 25 do 775


    if ((y >= 0 && y <= 60) || (y >= 740 && y <= 800)) {
        x = rand() % 851 + 25 ;
    } else {
     //   x = (rand() % 76 < 75) ? rand() % 76 + 25 : rand() % 76 + 800;
        x = (rand() % 2 < 1) ? rand() % 40 + 25 : rand() % 46 + 830;
    }

    //std::cout << x << y;

    return sf::Vector2f(x, y);
}

sf::Vector2f getRandomCordsForWalls() {


    //int x, y;
    /*
    if (availableX.empty() || availableY.empty()) {
        // Resetuj dostêpne wartoœci, jeœli wszystkie zosta³y u¿yte
        availableX = cordXarr;
        availableY = cordYarr;
    }
    */
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

