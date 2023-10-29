#include <SFML/Graphics.hpp>
#include "SettingsArrow.h"

SettingsArrow::SettingsArrow(int rotate, sf::Vector2f position, const std::string& texturePath, int &value) {
    sf::Texture arrowTexture;
    body.setSize(sf::Vector2f(20, 20));
    arrowTexture.loadFromFile("arrow.png");
    body.setTexture(&arrowTexture);
    body.setPosition(position);
    body.rotate(rotate);

    arrowValue = value;
}

void SettingsArrow::IncreaseValue() {
    arrowValue++;
}

void SettingsArrow::DecreaseValue() {
    arrowValue--;
}