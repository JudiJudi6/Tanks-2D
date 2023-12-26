#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Bullet.h"

class Box: public Wall
{
public:
	Box(sf::Vector2f position, sf::Texture* texture);
	void GetHitted(Bullet& bullet);
};

