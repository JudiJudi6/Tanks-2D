#include "WallsInGame.h"
#include <SFML/Graphics.hpp>

WallsInGame::WallsInGame(sf::Vector2f position) {
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

void WallsInGame::drawIncrease(sf::RenderWindow& window) {
    bodyIncrease.setPosition(position.x - 30, position.y - 30);

    window.draw(bodyIncrease);
}

void WallsInGame::drawDecrease(sf::RenderWindow& window) {
    bodyDecrease.setPosition(position.x + 50, position.y);
    bodyDecrease.rotate(0);

    window.draw(bodyDecrease);
}

void WallsInGame::IncreaseValue() {
    if (wallsInGame < 120) {
        wallsInGame++;
    }
}

void WallsInGame::DecreaseValue() {
    if (wallsInGame > 0) {
        wallsInGame--;
    }
}

void WallsInGame::SetTexture() {
    bodyIncrease.setTexture(&arrowTexture);
    bodyDecrease.setTexture(&arrowTexture);
}