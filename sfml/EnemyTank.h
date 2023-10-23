/*
#ifndef ENEMYTANK_H
#define ENEMYTANK_H
#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Bullet.h"

class EnemyTank : public Tank
{
private:
	sf::Texture texture;
	float speed;

public:
	EnemyTank(float x, float y, float speed, const std::string& texturePath) : Tank(x, y, speed, texturePath) {};
	//void getHitted(Bullet& playerBullet);
};

#endif // ENEMYTANK_H
*/