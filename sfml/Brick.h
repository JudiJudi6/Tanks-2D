#include "Wall.h"
#include <SFML/Graphics.hpp>
#include "Wall.h"

#pragma once
class Brick: public Wall 
{
public:
	Brick(sf::Vector2f position, sf::Texture* texture);
	void GetHitted(Bullet& bullet);
};

