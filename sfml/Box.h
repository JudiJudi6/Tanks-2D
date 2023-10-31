#include <SFML/Graphics.hpp>
#include "Bullet.h"

#pragma once
class Box
{
public:
	sf::RectangleShape body;

	Box(sf::Vector2f position);
	void GetHitted(Bullet& bullet);
};

