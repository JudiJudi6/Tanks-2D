#include "renderHelpers.h"
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
    static std::vector<int> cordXarr = { 125, 175, 225, 275, 325, 375, 525, 575, 625, 675, 725, 775 };
    static std::vector<int> cordYarr = { 125, 175, 225, 275, 325, 475, 525, 575, 625, 675 };

    static std::vector<int> availableX = cordXarr;
    static std::vector<int> availableY = cordYarr;

    int x, y;

    if (availableX.empty() || availableY.empty()) {
        // Resetuj dostêpne wartoœci, jeœli wszystkie zosta³y u¿yte
        availableX = cordXarr;
        availableY = cordYarr;
    }

    x = availableX[rand() % availableX.size()];
    y = availableY[rand() % availableY.size()];

    // Usuñ wybrane wartoœci z puli dostêpnych
    availableX.erase(std::remove(availableX.begin(), availableX.end(), x), availableX.end());
    availableY.erase(std::remove(availableY.begin(), availableY.end(), y), availableY.end());

    return sf::Vector2f(x, y);
}

