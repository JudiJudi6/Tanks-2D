#include "BoxesInGame.h"
#include <SFML/Graphics.hpp>

BoxesInGame::BoxesInGame(sf::Vector2f position) {
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

void BoxesInGame::drawIncrease(sf::RenderWindow& window) {
    bodyIncrease.setPosition(position.x - 30, position.y - 30);

    window.draw(bodyIncrease);
}

void BoxesInGame::drawDecrease(sf::RenderWindow& window) {
    bodyDecrease.setPosition(position.x + 50, position.y);
    bodyDecrease.rotate(0);

    window.draw(bodyDecrease);
}

void BoxesInGame::IncreaseValue() {
    if (boxesInGame < 120) {
        boxesInGame++;
    }
}

void BoxesInGame::DecreaseValue() {
    if (boxesInGame > 0) {
        boxesInGame--;
    }
}

void BoxesInGame::SetTexture() {
    bodyIncrease.setTexture(&arrowTexture);
    bodyDecrease.setTexture(&arrowTexture);
}