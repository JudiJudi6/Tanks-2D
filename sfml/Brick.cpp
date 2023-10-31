#include "Brick.h"
#include "Wall.h"
#include "enemyIntelligence.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"

Brick::Brick(sf::Vector2f position) {
    this->body.setSize(sf::Vector2f(50, 50));
    this->body.setPosition(position);
    this->body.setTexture(&brickTexture);
    this->body.setOrigin(sf::Vector2f(25, 25));
}

void Brick::GetHitted(Bullet& bullet) {
    sf::FloatRect wallBounds = body.getGlobalBounds();
    sf::FloatRect bulletBounds = bullet.body.getGlobalBounds();

    if (wallBounds.intersects(bulletBounds)) {
        body.setPosition(sf::Vector2f(2000, 2000));
        bullet.setActive(false);
    }
}