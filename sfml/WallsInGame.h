#include <SFML/Graphics.hpp>
#pragma once
class WallsInGame
{
private:
	sf::Texture arrowTexture;
	sf::Vector2f position;
public:
	sf::RectangleShape bodyIncrease;
	sf::RectangleShape bodyDecrease;
	int wallsInGame = 15;
	WallsInGame(sf::Vector2f position);
	void IncreaseValue();
	void DecreaseValue();
	void drawIncrease(sf::RenderWindow& window);
	void drawDecrease(sf::RenderWindow& window);
	void SetTexture();
};

