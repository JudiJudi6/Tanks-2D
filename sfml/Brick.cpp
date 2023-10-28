#include "Brick.h"
#include "Wall.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"

Brick::Brick(sf::Vector2f position, const std::string& textureWallPath) : Wall(position, textureWallPath) {
    this->body.setSize(sf::Vector2f(50, 50));
    this->body.setPosition(position);

    if (!wallTexture.loadFromFile(textureWallPath)) {
        std::cout << "B³¹d ³adowania tekstury: " << textureWallPath << std::endl;
    }
    // body.setTexture(&wallTexture);

    this->body.setOrigin(sf::Vector2f(25, 25));
}

void Brick::SetWallTexture() {
    this->body.setTexture(&wallTexture);
}

void Brick::GetHitted(Bullet& bullet) {
    sf::FloatRect wallBounds = body.getGlobalBounds();
    sf::FloatRect bulletBounds = bullet.body.getGlobalBounds();

    if (wallBounds.intersects(bulletBounds)) {
        body.setPosition(sf::Vector2f(2000, 2000));
        //std::cout << "brick";
        bullet.setActive(false);
    }
}