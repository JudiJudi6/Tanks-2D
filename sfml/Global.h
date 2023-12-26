#pragma once
#include <SFML/Graphics.hpp>
#include "Box.h"
#include "Wall.h"
#include "Brick.h"
#include "Tank.h"
#include "BonusEvent.h"
#include "Mine.h"

class Global {
private:
    Global();

public:
    static Global& getInstance() {
        static Global instance;
        return instance;
    }

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

    sf::Vector2f getRandomCordsForEnemySpawn();
    sf::Vector2f getRandomCordsForWalls();
    void clearVectors();
    void loadTextures();
};
