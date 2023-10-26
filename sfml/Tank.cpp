#include "Tank.h"
#include "Bullet.h"
#include "StatsWindow.h"
#include "enemyIntelligence.h"
#include <iostream>

Tank::Tank(sf::Vector2f position, float speed, const std::string& texturePath, const std::string& texturePathHitted) {
    this->speed = speed;
    this->body.setSize(sf::Vector2f(50, 50));
    this->body.setPosition(position);
    this->stopped = false;

    if (!texture.loadFromFile(texturePath)) {
        std::cout << "B³¹d ³adowania tekstury: " << texturePath << std::endl;
    }

    if (!textureHitted.loadFromFile(texturePathHitted)) {
        std::cout << "B³¹d ³adowania tekstury: " << texturePathHitted << std::endl;
    }

    this->body.setOrigin(sf::Vector2f(25, 25));


    this->healthPoints = 300;
}


void Tank::moveLeft() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(-5.0f, 0);
    

    if (position.x - speed >= 25) {
        this->stopped = false;
        body.move(-speed, 0);
        body.setRotation(180);
    }
    else {
        this->stopped = true;
    }
}

void Tank::moveRight() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(5.0f, 0);

    if (position.x + speed <= 875) {
        this->stopped = false;
        body.move(speed, 0);
        body.setRotation(0);
    }
    else {
        this->stopped = true;
    }
}

void Tank::moveTop() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(0, -5.0f);

    if (position.y - speed >= 25) {
        this->stopped = false;
        body.move(0, -speed);
        body.setRotation(-90);
    }
    else {
        this->stopped = true;
    }
}

void Tank::moveBottom() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(0, 5.0f);

    if (position.y + speed <= 775) {
        this->stopped = false;
        body.move(0, speed);
        body.setRotation(90);
    }
    else {
        this->stopped = true;
    }
}

sf::Vector2f Tank::getBulletDirection() {
    return direction;
}

void Tank::getHitted(Bullet& playerBullet) {
    sf::FloatRect enemyBounds = body.getGlobalBounds();
    sf::FloatRect bulletBounds = playerBullet.body.getGlobalBounds();
    //addKill();
    // kolizja
    if (enemyBounds.intersects(bulletBounds)) {
       // std::cout << "hitted";
        //std::cout << playerBullet.getDamage();
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
    else {
        body.setTexture(&texture);
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
    addKill();
}

void Tank::drawTank(sf::RenderWindow& window) {
    window.draw(this->body); 
}

bool Tank::getStopped() {
    return this->stopped;
}

int Tank::getRandomDirection(sf::Clock &clock) {
    static int nextChangeTime = std::rand() % 3000 + 500;
    static int newDirection = std::rand() % 4;
    sf::Time elapsedTime = clock.getElapsedTime();

    if (elapsedTime.asMilliseconds() > nextChangeTime) {
        newDirection = std::rand() % 4;
        nextChangeTime = std::rand() % 3000 + 500;
        clock.restart();
    }
    
    std::cout << nextChangeTime << " " << elapsedTime.asMilliseconds() << std::endl;
    return newDirection;
}

void Tank::setNewDirection(int newDirection) {
    this->newDirection = newDirection;
}

int Tank::getNewDirection() {
    return this->newDirection;
}

void Tank::enemyIntelligence(Tank& playerTank, Bullet& enemyBullet, sf::Clock& clock) {
    float deltaX = body.getPosition().x - playerTank.body.getPosition().x;
    float deltaY = body.getPosition().y - playerTank.body.getPosition().y;
    //newDirection = std::rand() % 4;
    sf::Time elapsedTime = clock.getElapsedTime();
 
    

    //sf::Time elapsedTime = clock.getElapsedTime();
    //newDirection = generateRandomNumber(0, 4);
    //timeToChangeDirection = generateRandomNumber(3000, 15000);
    //std::cout << timeToChangeDirection << std::endl;


    //enemyTank.getRandomDirection();





    if (std::abs(deltaY) < 22 || std::abs(deltaX) < 22) {

        if (std::abs(deltaY) < 22) {
            if (deltaX < 0) {
                moveRight();
                enemyBullet.shot(getBulletDirection(), body.getPosition().x, body.getPosition().y);
            }
            else {
                moveLeft();
                enemyBullet.shot(getBulletDirection(), body.getPosition().x, body.getPosition().y);
            }
        }
        if (std::abs(deltaX) < 22) {
            if (deltaY < 0) {
                moveBottom();
                enemyBullet.shot(getBulletDirection(), body.getPosition().x, body.getPosition().y);
            }
            else {
                moveTop();
                enemyBullet.shot(getBulletDirection(), body.getPosition().x, body.getPosition().y);
            }
        }
        //enemyTank.setInitial(false);
    }
    else {
        if (getStopped()) {
            newDirection = std::rand() % 4;
        }

        if (newDirection == 0) {
            moveBottom();
        }
        if (newDirection == 1) {
            moveTop();
        }
        if (newDirection == 2) {
            moveLeft();
        }
        if (newDirection == 3) {
            moveRight();
        }

        if (elapsedTime.asMilliseconds() > newDirectionChangeTime) {
            newDirection = std::rand() % 4;
            newDirectionChangeTime = std::rand() % 3000 + 500;
            clock.restart();
        }
        //else {
    //		clock.restart();
        //}
        //enemyTank.setInitial(false);
    }

    //std::cout << "X: " << enemyTank.body.getPosition().x << " Y: " << enemyTank.body.getPosition().y;
    //std::cout << "X: " << oldEnemyPosition.x << " Y: " << oldEnemyPosition.y << std::endl;
    oldEnemyPosition = body.getPosition();
}

