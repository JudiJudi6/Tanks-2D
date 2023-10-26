#include "Wall.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bullet.h"

Wall::Wall(sf::Vector2f position, const std::string& textureWallPath) {
    this->body.setSize(sf::Vector2f(50, 50));
    this->body.setPosition(position);

    if (!wallTexture.loadFromFile(textureWallPath)) {
        std::cout << "B³¹d ³adowania tekstury: " << textureWallPath << std::endl;
    }
   // body.setTexture(&wallTexture);

    this->body.setOrigin(sf::Vector2f(25, 25));
}

void Wall::SetWallTexture() {
    this->body.setTexture(&wallTexture);
}