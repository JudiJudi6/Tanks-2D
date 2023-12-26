#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
private:
    sf::Texture texture; //tekstura
    sf::Vector2f velocity; //prêdkoœæ pocisku
    sf::Clock shotClock; //zegar, co 2 sekundy mo¿na ponownie wystrzeliæ
    int damage; //uszkodzenia na strza³

public:
    Bullet();
    bool active;
    sf::RectangleShape body;

    void shot(sf::Vector2f direction, float x, float y, int damage = 100);
    void setActive(bool isActive);
    void drawBullet(sf::RenderWindow& window);
    void updateBullet();

    int getDamage();
};

