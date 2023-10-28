#include <SFML/Graphics.hpp>
#include "Bullet.h"

#pragma once
class Box
{
private:
	sf::Texture wallTexture;
public:
	sf::RectangleShape body;

	Box(sf::Vector2f position, const std::string& textureWallPath);
	void SetWallTexture();
	void GetHitted(Bullet& bullet);
};

