#include <SFML/Graphics.hpp>
#include "Bullet.h"

#pragma once
class Wall
{
private:
	sf::Texture wallTexture;

public:
	sf::RectangleShape body;

	Wall(sf::Vector2f position, const std::string& textureWallPath);
	void SetWallTexture();
};

