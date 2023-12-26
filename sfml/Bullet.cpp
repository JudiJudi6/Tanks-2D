 #include "Bullet.h"

Bullet::Bullet() {
    body.setSize(sf::Vector2f(10, 5));
    texture.loadFromFile("bullet.png");
    body.setOrigin(sf::Vector2f(5, 2.5));
    active = false;
    shotClock.restart();

    damage = 100;
}

void Bullet::shot(sf::Vector2f direction, float x, float y, int damage){
    this->active = true;
    this->damage = damage;

    if (active) {
        if (shotClock.getElapsedTime().asSeconds() >= 1.0) { 
            shotClock.restart(); 
            if (direction.x > 0 && direction.y == 0) {
                body.setRotation(0);
            }
            else if(direction.x < 0 && direction.y == 0){
                body.setRotation(180);
            }
            else if (direction.x == 0 && direction.y > 0) {
                body.setRotation(90);
            }
            else if (direction.x == 0 && direction.y < 0) {
                body.setRotation(-90);
            }
            body.setPosition(x, y);
            this->velocity = direction;
        }
    }
}

void Bullet::updateBullet() { // metoda "poruszaj¹ca pociskiem"
    this->body.setTexture(&texture);
     this->body.move(velocity);
}

void Bullet::setActive(bool isActive) { // metoda zmieniaj¹ca aktywnoœæ pocisku
    active = isActive;
    body.setPosition(10000, 10000);
}

void Bullet::drawBullet(sf::RenderWindow& window) { // metoda rysuj¹ca
    if (active) {
        window.draw(body);
    }
}

int Bullet::getDamage() { // getter uszkodzeñ pocisku
    return damage;
}