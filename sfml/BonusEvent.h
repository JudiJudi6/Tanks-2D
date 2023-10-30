#include "Tank.h"
#include <SFML/Graphics.hpp>
#pragma once
class BonusEvent
{
private:
	int flag;
	sf::Texture texture1;
	sf::Texture texture2;
	sf::Texture texture3;
	sf::Texture texture4;
public:
	BonusEvent(int flag, sf::Vector2f position);
	void drawEvent(sf::RenderWindow& window);
	void action(Tank &tank);

	sf::RectangleShape body;
};

