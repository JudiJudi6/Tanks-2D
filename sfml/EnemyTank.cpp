/*
#include "EnemyTank.h"
#include "Bullet.h"
#include <iostream>

EnemyTank::EnemyTank(float x, float y, float speed, const std::string& texturePath) : Tank(x, y, speed, texturePath) {
    this->speed = speed;
    body.setSize(sf::Vector2f(50, 50));
    body.setPosition(x, y);
    texture.loadFromFile(texturePath);
    body.setOrigin(sf::Vector2f(25, 25));

    body.setTexture(&texture);
}

/*
void EnemyTank::getHitted(Bullet& playerBullet) {
    // Pobierz granice obiektów
    sf::FloatRect enemyBounds = body.getGlobalBounds();
    sf::FloatRect bulletBounds = playerBullet.body.getGlobalBounds();

    // SprawdŸ, czy wystêpuje kolizja
    if (enemyBounds.intersects(bulletBounds)) {
        std::cout << "dupa";
    }
}
*/