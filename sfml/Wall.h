#include <SFML/Graphics.hpp>
#include "Bullet.h"

#pragma once
class Wall
{
private:

public:
	sf::RectangleShape body;

	Wall(sf::Vector2f position);
	void GetHitted(Bullet& bullet);
};

