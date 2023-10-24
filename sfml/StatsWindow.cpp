#include <SFML/Graphics.hpp>
#include "StatsWindow.h"

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