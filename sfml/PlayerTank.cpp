/*
#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "PlayerTank.h"

PlayerTank::PlayerTank(sf::Vector2f position, float speed, const std::string& texturePath, const std::string& texturePathHitted) : Tank(position, speed, texturePath, texturePathHitted) {};


void PlayerTank::moveLeft() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(-10.0f, 0);

    body.setRotation(180);
    if (position.x - speed >= 25 && !castRays(sf::Vector2f(-0.1f, 0))) {
        body.move(-speed, 0);
    }
}

void PlayerTank::moveRight() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(10.0f, 0);

    body.setRotation(0);
    if (position.x + speed <= 875 && !castRays(sf::Vector2f(0.1f, 0))) {
        body.move(speed, 0);
    }

}

void PlayerTank::moveTop() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(0, -10.0f);

    body.setRotation(-90);
    if (position.y - speed >= 25 && !castRays(sf::Vector2f(0, -0.1))) {
        body.move(0, -speed);
    }
}

void PlayerTank::moveBottom() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(0, 10.0f);

    body.setRotation(90);
    if (position.y + speed <= 775 && !castRays(sf::Vector2f(0, 0.1))) {
        body.move(0, speed);
    }
}
*/