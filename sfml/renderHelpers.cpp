#include "renderHelpers.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

sf::Vector2f getRandomCordsForEnemySpawn() {
    int x, y;

    y = rand() % 751 + 25; // 25 do 775


    if ((y >= 0 && y <= 120) || (y >= 680 && y <= 800)) {
        x = rand() % 851 + 25 ;
    } else {
        x = (rand() % 96 < 75) ? rand() % 96 + 25 : rand() % 96 + 780; //  25 do 120 lub od 780 do 875
    }

    //std::cout << x << y;

    return sf::Vector2f(x, y);
}

sf::Vector2f getRandomCordsForWalls() {
    int x, y;

    y = rand() % 560 + 120; // 25 do 775


    if ((y >= 120 && y <= 350) || (y >= 450 && y <= 680)) {
        x = rand() % 660 + 120;
    }
    else {
        x = (rand() % 281 < 75) ? rand() % 281 + 120 : rand() % 281 + 500;
    }

    return sf::Vector2f(x, y);
}
