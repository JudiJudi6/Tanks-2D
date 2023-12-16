#include "Wall.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "renderHelpers.h"
#include "Bullet.h"
#include "globals.h"

Wall::Wall(sf::Vector2f position) {
    this->body.setSize(sf::Vector2f(50, 50));
    this->body.setPosition(position);

    body.setTexture(&wallTexture);

    this->body.setOrigin(sf::Vector2f(25, 25));
}

void Wall::GetHitted(Bullet &bullet) {
    sf::FloatRect wallBounds = body.getGlobalBounds();
    sf::FloatRect bulletBounds = bullet.body.getGlobalBounds();
    if (wallBounds.intersects(bulletBounds)) {
       bullet.setActive(false);
    }
}