#include "Player.h"

Player::Player(float x, float y) {
    body.setSize(sf::Vector2f(50, 30));
    body.setFillColor(sf::Color::Green);
    body.setPosition(x, y);

    texture.loadFromFile("tank_texture.png"); // Za³ó¿, ¿e masz plik "tank_texture.png" w tym samym katalogu co twój kod
    body.setTexture(&texture);
}

void Player::move(float offsetX, float offsetY) {
    body.move(offsetX, offsetY);
}

sf::Vector2f Player::getPosition() const {
    return body.getPosition();
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(body);
}

void Player::rotate(float angle) {
    body.rotate(angle);
}

float Player::left() const {
    return body.getPosition().x;
}

float Player::top() const {
    return body.getPosition().y;
}

float Player::right() const {
    return body.getPosition().x + body.getSize().x;
}

float Player::bottom() const {
    return body.getPosition().y + body.getSize().y;
}
