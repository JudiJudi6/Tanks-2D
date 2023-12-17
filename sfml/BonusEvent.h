#include "Tank.h"
#include <SFML/Graphics.hpp>
#pragma once
class BonusEvent
{
private:
	int flag;
public:
	BonusEvent(int flag, sf::Vector2f position);
	void drawEvent(sf::RenderWindow& window);
	void action(Tank &tank);
	void getDestroyed(Bullet &bullet);

	sf::RectangleShape body;
};

