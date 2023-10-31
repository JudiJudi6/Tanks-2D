#include "Wall.h"
#include <SFML/Graphics.hpp>

#pragma once
class Brick 
{
public:
	sf::RectangleShape body;

	Brick(sf::Vector2f position);
	void GetHitted(Bullet& bullet);
};

