#include <SFML/Graphics.hpp>
#include "enemyIntelligence.h"
#include "Tank.h"
#include "Bullet.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include "Wall.h"
#include "Brick.h"	
#include "Box.h"

std::vector<Wall> walls;
std::vector<Brick> bricks;
std::vector<Box> boxes;
std::vector<Tank> enemyTanks;
std::vector<Bullet> enemyBullets;
std::vector<sf::Vector2f> availablePlace;
std::vector<BonusEvent> bonusEvents;


int generateRandomNumber(int min, int max) {
	//std::srand(time(0));

	int number = std::rand() % max + min;

	//std::cout << number << std::endl;

	return number;


}
/*
sf::Vector2f oldEnemyPosition = sf::Vector2f(0.0f, 0.0f);
	//int newDirection ; 
	//int timeToChangeDirection;

	//std::random_device rd;  // Inicjalizacja generatora liczb losowych
	//std::mt19937 gen(rd()); // Inicjalizacja generatora ziarnem z urz¹dzenia losowego
	//std::uniform_int_distribution<> distrib(min, max); // Dystrybucja liczb ca³kowitych od min do max

	//return distrib(gen);
int generateRandomNumber(int min, int max) {
	//std::srand(time(0));

	int number = std::rand() % max + min;

	//std::cout << number << std::endl;

	return number;


}
	

void enemyIntelligence(Tank& enemyTank, Tank& playerTank, Bullet& enemyBullet, sf::Clock &clock) {
	float deltaX = enemyTank.body.getPosition().x - playerTank.body.getPosition().x;
	float deltaY = enemyTank.body.getPosition().y - playerTank.body.getPosition().y;

	enemyTank.setNewDirection(enemyTank.getRandomDirection(clock));

	//sf::Time elapsedTime = clock.getElapsedTime();
	//newDirection = generateRandomNumber(0, 4);
	//timeToChangeDirection = generateRandomNumber(3000, 15000);
	//std::cout << timeToChangeDirection << std::endl;


	//enemyTank.getRandomDirection();



	
	
	if (std::abs(deltaY) < 22 || std::abs(deltaX) < 22) {

		if (std::abs(deltaY) < 22) {
			if (deltaX < 0) {
				enemyTank.moveRight();
				enemyBullet.shot(enemyTank.getBulletDirection(), enemyTank.body.getPosition().x, enemyTank.body.getPosition().y);
			}
			else {
				enemyTank.moveLeft();
				enemyBullet.shot(enemyTank.getBulletDirection(), enemyTank.body.getPosition().x, enemyTank.body.getPosition().y);
			}
		}
		if (std::abs(deltaX) < 22) {
			if (deltaY < 0) {
				enemyTank.moveBottom();
				enemyBullet.shot(enemyTank.getBulletDirection(), enemyTank.body.getPosition().x, enemyTank.body.getPosition().y);
			}
			else {
				enemyTank.moveTop();
				enemyBullet.shot(enemyTank.getBulletDirection(), enemyTank.body.getPosition().x, enemyTank.body.getPosition().y);
			}
		}
		//enemyTank.setInitial(false);
	}
	else {
		if (enemyTank.getStopped()) {
			enemyTank.setNewDirection(enemyTank.getRandomDirection(clock));
		}

		if (enemyTank.getNewDirection() == 0) {
			enemyTank.moveBottom();
		}
		if (enemyTank.getNewDirection() == 1) {
			enemyTank.moveTop();
		}
		if (enemyTank.getNewDirection() == 2) {
			enemyTank.moveLeft();
		}
		if (enemyTank.getNewDirection() == 3) {
			enemyTank.moveRight();
		}

		//if (elapsedTime.asMilliseconds() < 2000) {
		//}
		//else {
	//		clock.restart();
		//}
		//enemyTank.setInitial(false);
	}
	
	//std::cout << "X: " << enemyTank.body.getPosition().x << " Y: " << enemyTank.body.getPosition().y;
	//std::cout << "X: " << oldEnemyPosition.x << " Y: " << oldEnemyPosition.y << std::endl;
	oldEnemyPosition = enemyTank.body.getPosition();
}


*/