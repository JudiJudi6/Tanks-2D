#include <SFML/Graphics.hpp>
#pragma once
class TanksInGame
{
private:
	sf::Texture arrowTexture;
	sf::Vector2f position;
public:
	sf::RectangleShape bodyIncrease;
	sf::RectangleShape bodyDecrease;
	int tanksInGame = 1;
	TanksInGame(sf::Vector2f position);
	void IncreaseValue();
	void DecreaseValue();
	void drawIncrease(sf::RenderWindow &window);
	void drawDecrease(sf::RenderWindow &window);
	void SetTexture();
};

