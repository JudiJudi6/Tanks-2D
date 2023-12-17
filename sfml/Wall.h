#include <SFML/Graphics.hpp>
#include "Bullet.h"

#pragma once
class Wall
{
private:
public:
	Wall(sf::Vector2f position, sf::Texture* texture);
	void GetHitted(Bullet& bullet);
	sf::RectangleShape body;
};

