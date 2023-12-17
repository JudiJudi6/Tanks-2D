#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Wall.h"

#pragma once
class Box: public Wall
{
public:
	Box(sf::Vector2f position, sf::Texture* texture);
	void GetHitted(Bullet& bullet);
};

