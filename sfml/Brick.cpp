#include "Brick.h"
#include "Wall.h"
#include "renderHelpers.h"
#include <SFML/Graphics.hpp>
#include "Bullet.h"

Brick::Brick(sf::Vector2f position, sf::Texture* texture) : Wall(position, texture) {}

void Brick::GetHitted(Bullet& bullet) {
    sf::FloatRect wallBounds = body.getGlobalBounds();
    sf::FloatRect bulletBounds = bullet.body.getGlobalBounds();

    if (wallBounds.intersects(bulletBounds)) {
        body.setPosition(sf::Vector2f(2000, 2000));
        bullet.setActive(false);
    }
}