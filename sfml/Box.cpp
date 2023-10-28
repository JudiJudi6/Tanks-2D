#include "Box.h"
#include <iostream>


Box::Box(sf::Vector2f position, const std::string& textureWallPath){
    this->body.setSize(sf::Vector2f(50, 50));
    this->body.setPosition(position);

    if (!wallTexture.loadFromFile(textureWallPath)) {
        std::cout << "B³¹d ³adowania tekstury: " << textureWallPath << std::endl;
    }
    this->body.setOrigin(sf::Vector2f(25, 25));
}

void Box::SetWallTexture() {
    this->body.setTexture(&wallTexture);
}

void Box::GetHitted(Bullet& bullet) {
    sf::FloatRect boxBounds = body.getGlobalBounds();
    sf::FloatRect bulletBounds = bullet.body.getGlobalBounds();

    if (boxBounds.intersects(bulletBounds)) {
        body.setPosition(sf::Vector2f(2000, 2000));
        std::cout << "box";
        bullet.setActive(false);
    }
}