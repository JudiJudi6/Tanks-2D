#include "Wall.h"
#include <SFML/Graphics.hpp>

#pragma once
class Brick : public Wall 
{
private:
	sf::Texture wallTexture;
public:
	sf::RectangleShape body;

	Brick(sf::Vector2f position, const std::string& textureWallPath);
	void SetWallTexture();
	void GetHitted(Bullet& bullet);
};

