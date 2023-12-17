#include "Tank.h"
#include "Bullet.h"
#include "StatsWindow.h"
#include "renderHelpers.h"
#include "BonusEvent.h"
#include "Mine.h"
#include <iostream>

Tank::Tank(sf::Vector2f position, float speed, int flag) {
    this->speed = speed;
    this->body.setSize(sf::Vector2f(45, 45));
    this->body.setPosition(position);
    this->stopped = false;

    if (flag == 1) {
        texture = playerTexture;
        textureHitted = playerTextureHitted;
    }
    else if (flag == 0) {
        texture = enemyTexture;
        textureHitted = enemyTextureHitted;
    }
    this->body.setOrigin(sf::Vector2f(22.5, 22.5));
    this->healthPoints = 300;
}


void Tank::moveLeft() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(-20.0f, 0);

    body.setRotation(180);

    if (!castRays(sf::Vector2f(-5.0f, 0))) { 
        if (position.x - speed >= 25) {
            body.move(-speed, 0);
            this->stopped = false;
        }
        else {
            this->stopped = true;
        }
    }
    else {
        this->stopped = true;
    }
}

void Tank::moveRight() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(20.0f, 0);

    body.setRotation(0);

    if (!castRays(sf::Vector2f(5.0f, 0))) { 
        if (position.x + speed <= 875) {
            body.move(speed, 0);
            this->stopped = false;
        }
        else {
            this->stopped = true;
        }
    }
    else {
        this->stopped = true;
    }
}

void Tank::moveTop() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(0, -20.0f);

    body.setRotation(-90);

    if (!castRays(sf::Vector2f(0, -5.0f))) { 
        if (position.y - speed >= 25) {
            body.move(0, -speed);
            this->stopped = false;
        }
        else {
            this->stopped = true;
        }
    }
    else {
        this->stopped = true;
    }
}

void Tank::moveBottom() {
    sf::Vector2f position = body.getPosition();
    direction = sf::Vector2f(0, 20.0f);
    body.setRotation(90);

    if (!castRays(sf::Vector2f(0, 5.0f))) { 
        if (position.y + speed <= 775) {
            body.move(0, speed);
            this->stopped = false;
        }
        else {
            this->stopped = true;
        }
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
    if (enemyBounds.intersects(bulletBounds) || onMine) {
        isHitted = true;
        hitClock.restart();
        setHealthPoints(getHealthPoints() - playerBullet.getDamage());

        playerBullet.setActive(false);
        killed = getHealthPoints() <= 0;
        if (killed) {
            enemyGetKilled();
            killedTime = gameTimeClock.getElapsedTime();
            respawn = true;
            killed = false;
        }
        onMine = false;
    }
}

void Tank::respawnEnemy() {
    if (respawn) {
        if (killedTime.asSeconds() + 10 < gameTime) {
            setHealthPoints(300);
            body.setPosition(getRandomCordsForEnemySpawn());
            setHealthPoints(getHealthPoints() + 30);
            setDamage(getDamage() + 10);
            respawn = false;
            killedTime = gameTimeClock.getElapsedTime();
        }
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
    if (rand() % 3 > 0) {
        bonusEvents.push_back(BonusEvent(rand() % 4, body.getPosition()));
    }
    body.setPosition(11000, 11000);
    addKill();
}

void Tank::drawTank(sf::RenderWindow& window) {
    window.draw(this->body); 
}

bool Tank::getStopped() {
    return this->stopped;
}

void Tank::setStopped(bool isStop) {
    this->stopped = isStop;
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
    sf::Time elapsedTime = clock.getElapsedTime();

    if (!isWallBetweenTanks(playerTank) && (std::abs(deltaY) < 22 || std::abs(deltaX) < 22)) {
        if (std::abs(deltaY) < 22) {
            if (deltaX < 0) {
                moveRight();
                enemyBullet.shot(getBulletDirection(), body.getPosition().x, body.getPosition().y, getDamage());
            }
            else {
                moveLeft();
                enemyBullet.shot(getBulletDirection(), body.getPosition().x, body.getPosition().y, getDamage());
            }
        }
        if (std::abs(deltaX) < 22) {
            if (deltaY < 0) {
                moveBottom();
                enemyBullet.shot(getBulletDirection(), body.getPosition().x, body.getPosition().y, getDamage());
            }
            else {
                moveTop();
                enemyBullet.shot(getBulletDirection(), body.getPosition().x, body.getPosition().y, getDamage());
            }

        }
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
    }
    oldEnemyPosition = body.getPosition();
}

bool Tank::isWallBetweenTanks(const Tank& playerTank) {
    sf::FloatRect playerTankBounds = playerTank.body.getGlobalBounds();
    sf::FloatRect enemyTankBounds = body.getGlobalBounds();

    if (std::abs(playerTankBounds.top - enemyTankBounds.top) < 50) {
        float min_x = std::min(playerTankBounds.left, enemyTankBounds.left);
        float max_x = std::max(playerTankBounds.left + playerTankBounds.width, enemyTankBounds.left + enemyTankBounds.width);

        for (const Wall& wall : walls) {
            sf::FloatRect wallBounds = wall.body.getGlobalBounds();
            if (wallBounds.top + 20 > playerTankBounds.top && wallBounds.top + 20 < playerTankBounds.top + playerTankBounds.height &&
                wallBounds.left > min_x && wallBounds.left < max_x) {
                return true;
            }
        }
        for (const Brick& brick: bricks) {
            sf::FloatRect wallBounds = brick.body.getGlobalBounds();
            if (wallBounds.top + 20 > playerTankBounds.top && wallBounds.top + 20 < playerTankBounds.top + playerTankBounds.height &&
                wallBounds.left > min_x && wallBounds.left < max_x) {
                return true;
            }
        }
    }

    if (std::abs(playerTankBounds.left - enemyTankBounds.left) < 50){
        float min_y = std::min(playerTankBounds.top, enemyTankBounds.top);
        float max_y = std::max(playerTankBounds.top + playerTankBounds.height, enemyTankBounds.top + enemyTankBounds.height);

        for (const Wall& wall : walls) {
            sf::FloatRect wallBounds = wall.body.getGlobalBounds();
            if (wallBounds.left + 20 > playerTankBounds.left && wallBounds.left + 20 < playerTankBounds.left + playerTankBounds.width &&
                wallBounds.top > min_y && wallBounds.top < max_y) {
                return true; 
            }
        }
        for (const Brick& brick : bricks) {
            sf::FloatRect wallBounds = brick.body.getGlobalBounds();
            if (wallBounds.left + 20 > playerTankBounds.left && wallBounds.left + 20 < playerTankBounds.left + playerTankBounds.width &&
                wallBounds.top > min_y && wallBounds.top < max_y) {
                return true;
            }
        }
    }

    return false; 
}

bool Tank::castRays(const sf::Vector2f& newPosition) {
    sf::FloatRect tankBounds = body.getGlobalBounds();
    sf::RectangleShape shape;
    shape.setPosition(body.getPosition().x, body.getPosition().y);
    shape.setSize(sf::Vector2f(45, 45));
    shape.setOrigin(22.5, 22.5);
    shape.move(newPosition);
    
    for (const Wall& wall : walls) {
        sf::FloatRect wallBounds = wall.body.getGlobalBounds();

        if (wallBounds.intersects(shape.getGlobalBounds())) {
            return true; 
        }
    }

    for (const Brick& brick: bricks) {
        sf::FloatRect brickBounds = brick.body.getGlobalBounds();

        if (brickBounds.intersects(shape.getGlobalBounds())) {
            return true; 
        }
    }

    for (const Box& box: boxes) {
        sf::FloatRect boxBounds = box.body.getGlobalBounds();

        if (boxBounds.intersects(shape.getGlobalBounds())) {
            return true; 
        }
    }

    return false; 
}

void Tank::eventBonusIntersects() {
    for (BonusEvent& bonusEvent : bonusEvents) {
        sf::FloatRect tankBounds = body.getGlobalBounds();
        sf::FloatRect bonusBounds = bonusEvent.body.getGlobalBounds();

        if (tankBounds.intersects(bonusBounds)) {
            bonusEvent.action(*this);
        }
    }
}

void Tank::mineIntersects() {
    for (Mine& mine : minesOnMap) {
        sf::FloatRect tankBounds = body.getGlobalBounds();
        sf::FloatRect mineBounds = mine.body.getGlobalBounds();

        if (tankBounds.intersects(mineBounds)) {
            this->setHealthPoints(getHealthPoints() - 300);
            onMine = true;
            mine.body.setPosition(-100, -100);
        }
    }
}

void Tank::setDamage(int dmg) {
    this->damagePerShot = dmg;
}

int Tank::getDamage() {
    return this->damagePerShot;
}

void Tank::setSpeed(float speed) {
    if (speed <= 5.0f) {
        this->speed = speed;
    }
}

float Tank::getSpeed() {
    return this->speed;
}

void Tank::setAddMines() {
    this->mines++;
}

void Tank::setMines(int mines) {
    this->mines = mines;
}

void Tank::useOneMine() {
    this->mines--;
}

int Tank::getMines() {
    return this->mines;
}