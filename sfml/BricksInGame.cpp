#include "BricksInGame.h"
#include <SFML/Graphics.hpp>

BricksInGame::BricksInGame(sf::Vector2f position) {
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

void BricksInGame::drawIncrease(sf::RenderWindow& window) {
    bodyIncrease.setPosition(position.x - 30, position.y - 30);

    window.draw(bodyIncrease);
}

void BricksInGame::drawDecrease(sf::RenderWindow& window) {
    bodyDecrease.setPosition(position.x + 50, position.y);
    bodyDecrease.rotate(0);

    window.draw(bodyDecrease);
}

void BricksInGame::IncreaseValue() {
    if (bricksInGame < 120) {
        bricksInGame++;
    }
}

void BricksInGame::DecreaseValue() {
    if (bricksInGame > 0) {
        bricksInGame--;
    }
}

void BricksInGame::SetTexture() {
    bodyIncrease.setTexture(&arrowTexture);
    bodyDecrease.setTexture(&arrowTexture);
}