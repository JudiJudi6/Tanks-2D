#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>

class Bullet
{
private:
    sf::Texture texture;
    sf::Vector2f velocity;
    sf::Clock shotClock;
    int damage;

public:
    Bullet();
    bool active;
    sf::RectangleShape body;

    void shot(sf::Vector2f direction, float x, float y);
    void setActive(bool isActive);
    void drawBullet(sf::RenderWindow& window);
    void updateBullet();

    int getDamage();
};

#endif // BULLET_H

