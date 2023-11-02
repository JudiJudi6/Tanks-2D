#include "Box.h"
#include "BonusEvent.h"
#include "globals.h"
#include <iostream>


Box::Box(sf::Vector2f position){
    this->body.setSize(sf::Vector2f(50, 50));
    this->body.setPosition(position);


    this->body.setOrigin(sf::Vector2f(25, 25));
    this->body.setTexture(&boxTexture);
}

void Box::GetHitted(Bullet& bullet) {
    sf::FloatRect boxBounds = body.getGlobalBounds();
    sf::FloatRect bulletBounds = bullet.body.getGlobalBounds();

    if (boxBounds.intersects(bulletBounds)) {
        bullet.setActive(false);
        bonusEvents.push_back(BonusEvent(rand() % 4, body.getPosition()));
        body.setPosition(sf::Vector2f(2000, 2000));
        std::cout << bonusEvents.size();
    }
}