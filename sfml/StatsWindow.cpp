#include <SFML/Graphics.hpp>
#include "StatsWindow.h"
#include <iostream>

int destroyedTanks = 0;
int gameTime = 0;
bool countTime = false;
sf::Clock gameTimeClock;

void drawText(sf::RenderWindow& window, const std::string& text, int number, const sf::Vector2f& position) {
    sf::Font font;
    font.loadFromFile("roboto.ttf"); 

    sf::Text displayText;
    displayText.setFont(font);
    displayText.setCharacterSize(15);
    displayText.setFillColor(sf::Color::Black);

    std::string fullText = text + std::to_string(number);
    displayText.setString(fullText);
    displayText.setPosition(position);

    window.draw(displayText);
}

void addKill() {
    destroyedTanks++;
}

void startGameTime() {
    countTime = true;
    gameTimeClock.restart();
}

void countGameTime() {
    if (countTime) {
        gameTime = gameTimeClock.getElapsedTime().asSeconds();
    }
}

void stopGameTime() {
    countTime = false;
}