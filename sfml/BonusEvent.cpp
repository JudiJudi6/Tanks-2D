#include "BonusEvent.h"
#include "enemyIntelligence.h"

BonusEvent::BonusEvent(int flag, sf::Vector2f position) {
	this->flag = flag;
	
	body.setSize(sf::Vector2f(35, 35));
	body.setPosition(position);
	texture1.loadFromFile("health.png");
	texture2.loadFromFile("dmg.png");
	texture3.loadFromFile("dmg.png");
	texture4.loadFromFile("dmg.png");

	if (flag == 0) {
		body.setTexture(&texture1);
	}
	if (flag == 1) {
		body.setTexture(&texture2);
	}
	if (flag == 2) {
		body.setTexture(&texture3);
	}
	if (flag == 3) {
		body.setTexture(&texture3);
	}
	body.setOrigin(sf::Vector2f(17.5f, 17.5f));
}

void BonusEvent::drawEvent(sf::RenderWindow& window) {
	
	if (flag == 0) {
		body.setTexture(&texture1);
	}
	if (flag == 1) {
		body.setTexture(&texture2);
	}
	if (flag == 2) {
		body.setTexture(&texture3);
	}
	if (flag == 3) {
		body.setTexture(&texture3);
	}
   
	
    window.draw(body);
}

void BonusEvent::action(Tank &tank) {
	//hp bonus
	if (flag == 0) {
		tank.setHealthPoints(tank.getHealthPoints() + 50);
		body.setPosition(-100, -100);
	}

	//dmg bonus
	if (flag == 1) {
		tank.setDamage(tank.getDamage() + 20);
		body.setPosition(-100, -150);
	}

	//speed bonus
	if (flag == 2) {
		tank.setSpeed(tank.getSpeed() + 0.2);
		body.setPosition(-100, -200);
	}

	//bomb
	if (flag == 3) {
		tank.setHealthPoints(tank.getHealthPoints() - 300);
		body.setPosition(-100, -250);
	}
}