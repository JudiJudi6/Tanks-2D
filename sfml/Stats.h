#pragma once
#include <SFML/Graphics.hpp>
#include "Tank.h"

class Stats
{
private:
	int kills;
	int hp;
	int dmgBullet;
	sf::Clock gameClock;
public:
	Stats();
	void displayStats(sf::RenderWindow& window);
	
};