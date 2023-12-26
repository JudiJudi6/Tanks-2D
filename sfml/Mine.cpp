#include "Mine.h"
#include "Global.h"

Mine::Mine(sf::Vector2f position) {
    this->body.setSize(sf::Vector2f(25, 25));
    this->body.setPosition(position);
    this->body.setOrigin(sf::Vector2f(12.5, 12.5));
    this->body.setTexture(&Global::getInstance().bomb);
}
