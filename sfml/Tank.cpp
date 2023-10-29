#include "Tank.h"
#include "Bullet.h"
#include "StatsWindow.h"
#include "enemyIntelligence.h"
#include "renderHelpers.h"
#include <iostream>
#include "PlayerTank.h"

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
    direction = sf::Vector2f(-10.0f, 0);

    body.setRotation(180);

    if (!castRays(sf::Vector2f(-2.5f, 0))) { // SprawdŸ czy mo¿emy siê poruszyæ
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
    direction = sf::Vector2f(10.0f, 0);

    body.setRotation(0);

    if (!castRays(sf::Vector2f(2.5f, 0))) { // SprawdŸ czy mo¿emy siê poruszyæ
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
    direction = sf::Vector2f(0, -10.0f);

    body.setRotation(-90);

    if (!castRays(sf::Vector2f(0, -2.5f))) { // SprawdŸ czy mo¿emy siê poruszyæ
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
    direction = sf::Vector2f(0, 10.0f);

    body.setRotation(90);

    if (!castRays(sf::Vector2f(0, 2.5f))) { // SprawdŸ czy mo¿emy siê poruszyæ
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
    //addKill();
    //std::cout << "geth";
    // kolizja
    if (enemyBounds.intersects(bulletBounds)) {
        // std::cout << "hitted";
         //std::cout << playerBullet.getDamage();
        isHitted = true;
        hitClock.restart();
        setHealthPoints(getHealthPoints() - playerBullet.getDamage());
        killed = getHealthPoints() <= 0;


        if (killed) {
            enemyGetKilled();
            killedTime = gameTimeClock.getElapsedTime();
           // std::cout << "killed";
            respawn = true;
            killed = false;
        }  
        playerBullet.setActive(false);
    }
}

void Tank::respawnEnemy() {
    if (respawn) {
       // std::cout << killedTime.asSeconds() << std::endl;
        if (killedTime.asSeconds() + 10 < gameTime) {
            setHealthPoints(300);
            body.setPosition(getRandomCordsForEnemySpawn());
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





    if (!isWallBetweenTanks(playerTank) && (std::abs(deltaY) < 22 || std::abs(deltaX) < 22)) {
       // if (std::abs(deltaY) < 22 || std::abs(deltaX) < 22) {

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
       // }
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

bool Tank::isWallBetweenTanks(const Tank& playerTank) {
    sf::FloatRect playerTankBounds = playerTank.body.getGlobalBounds();
    sf::FloatRect enemyTankBounds = body.getGlobalBounds();

    // SprawdŸ, czy istnieje œciana miêdzy czo³gami w osi x
    if (std::abs(playerTankBounds.top - enemyTankBounds.top) < 50) {
        float min_x = std::min(playerTankBounds.left, enemyTankBounds.left);
        float max_x = std::max(playerTankBounds.left + playerTankBounds.width, enemyTankBounds.left + enemyTankBounds.width);

        for (const Wall& wall : walls) {
            sf::FloatRect wallBounds = wall.body.getGlobalBounds();
            if (wallBounds.top + 20 > playerTankBounds.top && wallBounds.top + 20 < playerTankBounds.top + playerTankBounds.height &&
                wallBounds.left > min_x && wallBounds.left < max_x) {
                return true; // Istnieje œciana w osi x
            }
        }
        for (const Brick& brick: bricks) {
            sf::FloatRect wallBounds = brick.body.getGlobalBounds();
            if (wallBounds.top + 20 > playerTankBounds.top && wallBounds.top + 20 < playerTankBounds.top + playerTankBounds.height &&
                wallBounds.left > min_x && wallBounds.left < max_x) {
                return true; // Istnieje œciana w osi x
            }
        }
    }

    // SprawdŸ, czy istnieje œciana miêdzy czo³gami w osi y
    if (std::abs(playerTankBounds.left - enemyTankBounds.left) < 50){
        float min_y = std::min(playerTankBounds.top, enemyTankBounds.top);
        float max_y = std::max(playerTankBounds.top + playerTankBounds.height, enemyTankBounds.top + enemyTankBounds.height);

        for (const Wall& wall : walls) {
            sf::FloatRect wallBounds = wall.body.getGlobalBounds();
            if (wallBounds.left + 20 > playerTankBounds.left && wallBounds.left + 20 < playerTankBounds.left + playerTankBounds.width &&
                wallBounds.top > min_y && wallBounds.top < max_y) {
                return true; // Istnieje œciana w osi y
            }
        }
        for (const Brick& brick : bricks) {
            sf::FloatRect wallBounds = brick.body.getGlobalBounds();
            if (wallBounds.left + 20 > playerTankBounds.left && wallBounds.left + 20 < playerTankBounds.left + playerTankBounds.width &&
                wallBounds.top > min_y && wallBounds.top < max_y) {
                return true; // Istnieje œciana w osi y
            }
        }
    }

    return false; // Brak œciany miêdzy czo³gami
}

bool Tank::castRays(const sf::Vector2f& newPosition) {
    sf::FloatRect tankBounds = body.getGlobalBounds();
    sf::RectangleShape shape;
    shape.setPosition(body.getPosition().x, body.getPosition().y);
    shape.setSize(sf::Vector2f(50, 50));
    shape.setOrigin(25, 25);
    shape.move(newPosition);
    
    
    //std::cout << "tank: " << body.getPosition().x << body.getPosition().y << std::endl;
    //std::cout << "cast: " << shape.getPosition().x << shape.getPosition().y << std::endl;

    for (const Wall& wall : walls) {
        sf::FloatRect wallBounds = wall.body.getGlobalBounds();

        // SprawdŸ, czy nowa pozycja czo³gu koliduje z œcian¹
        if (wallBounds.intersects(shape.getGlobalBounds())) {
           //std::cout << "kolizja";
            return true; // Kolizja
        }
    }

    for (const Brick& brick: bricks) {
        sf::FloatRect brickBounds = brick.body.getGlobalBounds();

        // SprawdŸ, czy nowa pozycja czo³gu koliduje z œcian¹
        if (brickBounds.intersects(shape.getGlobalBounds())) {
            //std::cout << "kolizja";
            return true; // Kolizja
        }
    }

    for (const Box& box: boxes) {
        sf::FloatRect boxBounds = box.body.getGlobalBounds();

        // SprawdŸ, czy nowa pozycja czo³gu koliduje z œcian¹
        if (boxBounds.intersects(shape.getGlobalBounds())) {
            //std::cout << "kolizja";
            return true; // Kolizja
        }
    }

    return false; // Brak kolizji
}