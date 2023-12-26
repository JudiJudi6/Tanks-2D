#include <SFML/Graphics.hpp>
#include "StatsWindow.h"
#include <iostream>

int destroyedTanks = 0;
int gameTime = 0;
bool countTime = false;
sf::Clock gameTimeClock;

void drawText(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, int number) {
    sf::Font font;
    font.loadFromFile("roboto.ttf"); 
    std::string fullText;
    sf::Text displayText;
    displayText.setFont(font);
    displayText.setCharacterSize(20);
    displayText.setFillColor(sf::Color::White);

    if (number == -1) {
        fullText = text;
    }
    else {
        fullText = text + std::to_string(number);
    }
    displayText.setString(fullText);
    displayText.setPosition(position);

    window.draw(displayText);
}

void drawTextFloat(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, float number) {
    sf::Font font;
    font.loadFromFile("roboto.ttf");
    std::string fullText;
    sf::Text displayText;
    displayText.setFont(font);
    displayText.setCharacterSize(20);
    displayText.setFillColor(sf::Color::White);

    if (number == -1) {
        fullText = text;
    }
    else {
        fullText = text + std::to_string(std::round(number * 10) / 10);
    }
    displayText.setString(fullText);
    displayText.setPosition(position);

    window.draw(displayText);
}
 
void addKill() { // dodaj zniszczenie
    destroyedTanks++;
}
 
void startGameTime() { // zegar start
    countTime = true;
    gameTimeClock.restart();
}

void countGameTime() { // funkcja licz¹ca czas w sekundach w zale¿noœci od flagi count time
    if (countTime) {
        gameTime = gameTimeClock.getElapsedTime().asSeconds();
    }
}

void stopGameTime() { // zegar stop
    countTime = false;
}