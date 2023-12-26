#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Bullet.h"

class Brick: public Wall 
{
public:
	Brick(sf::Vector2f position, sf::Texture* texture);
	void GetHitted(Bullet& bullet);
};

