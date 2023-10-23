#include "Tank.h"
#include "Bullet.h"
#include <iostream>

Tank::Tank(float x, float y, float speed, const std::string& texturePath, const std::string& texturePathHitted) {
    this->speed = speed;
    body.setSize(sf::Vector2f(50, 50));
    body.setPosition(x, y);
    texture.loadFromFile(texturePath);
    textureHitted.loadFromFile(texturePathHitted);
    body.setOrigin(sf::Vector2f(25, 25));

    body.setTexture(&texture);

    healthPoints = 300;
}

void Tank::moveLeft() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(-0.5f, 0);
    

    if (position.x - speed >= 25) {
        body.move(-speed, 0);
        body.setRotation(180);
    }
}

void Tank::moveRight() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(0.5f, 0);

    if (position.x + speed <= 875) {
        body.move(speed, 0);
        body.setRotation(0);
    }
}

void Tank::moveTop() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(0, -0.5f);

    if (position.y - speed >= 25) {
        body.move(0, -speed);
        body.setRotation(-90);
    }
}

void Tank::moveBottom() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(0, 0.5f);

    if (position.y + speed <= 775) {
        body.move(0, speed);
        body.setRotation(90);
    }
}

sf::Vector2f Tank::getBulletDirection() {
    return direction;
}

void Tank::getHitted(Bullet& playerBullet) {
    sf::FloatRect enemyBounds = body.getGlobalBounds();
    sf::FloatRect bulletBounds = playerBullet.body.getGlobalBounds();

    // kolizja
    if (enemyBounds.intersects(bulletBounds)) {
        std::cout << "hitted";
        std::cout << playerBullet.getDamage();
        isHitted = true;
        hitClock.restart();
        setHealthPoints(getHealthPoints() - playerBullet.getDamage());
        bool killed = getHealthPoints() <=0;
        if (killed) {
            enemyGetKilled();
        }
        playerBullet.setActive(false);
    }
}

void Tank::getHittedAnimation() {
    if (isHitted) {
        body.setTexture(&textureHitted);
        
            if (hitClock.getElapsedTime().asMilliseconds() > 50) {
                isHitted = false;
                body.setTexture(&texture);
            }
    }
}



int Tank::getHealthPoints() {
    return healthPoints;
}

void Tank::setHealthPoints(int points) {
    this->healthPoints = points;
}

void Tank::enemyGetKilled() {
    body.setPosition(11000, 11000);
    std::cout << "killed";
}