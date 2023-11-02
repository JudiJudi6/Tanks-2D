#include <SFML/Graphics.hpp>
#pragma once
class GameSpeed
{
private:
	sf::Texture arrowTexture;
	sf::Vector2f position;
public:
	sf::RectangleShape bodyIncrease;
	sf::RectangleShape bodyDecrease;
	float gameSpeed = 2;
	GameSpeed(sf::Vector2f position);
	void IncreaseValue();
	void DecreaseValue();
	void drawIncrease(sf::RenderWindow& window);
	void drawDecrease(sf::RenderWindow& window);
	void SetTexture();
	float getGameSpeed();
};

