#include "GameSpeed.h"
#include "BoxesInGame.h"
#include <SFML/Graphics.hpp>

GameSpeed::GameSpeed(sf::Vector2f position) {
    bodyIncrease.setSize(sf::Vector2f(20, 20));
    bodyDecrease.setSize(sf::Vector2f(20, 20));
    arrowTexture.loadFromFile("arrow.png");
    bodyIncrease.setTexture(&arrowTexture);
    bodyDecrease.setTexture(&arrowTexture);
    bodyDecrease.setOrigin(25, 25);
    bodyIncrease.setOrigin(25, 25);
    this->position = position;
    bodyIncrease.rotate(180);
}

void GameSpeed::drawIncrease(sf::RenderWindow& window) {
    bodyIncrease.setPosition(position.x - 30, position.y - 30);

    window.draw(bodyIncrease);
}

void GameSpeed::drawDecrease(sf::RenderWindow& window) {
    bodyDecrease.setPosition(position.x + 50, position.y);
    bodyDecrease.rotate(0);

    window.draw(bodyDecrease);
}

void GameSpeed::IncreaseValue() {
    if (gameSpeed < 6) {
        gameSpeed = gameSpeed + 0.1f;
    }
}

void GameSpeed::DecreaseValue() {
    if (gameSpeed > 0) {
        gameSpeed = gameSpeed - 0.1f;
    }
}

void GameSpeed::SetTexture() {
    bodyIncrease.setTexture(&arrowTexture);
    bodyDecrease.setTexture(&arrowTexture);
}

float GameSpeed::getGameSpeed() {
    return gameSpeed;
}