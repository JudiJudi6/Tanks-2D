#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Bullet.h"
#include "EnemyTank.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1100, 800), "Tanks 2D", sf::Style::Close);
    sf::RectangleShape map;
    sf::RectangleShape panel;

    // Gracz
    Tank playerTank(100, 100, 0.1f, "player.png", "playerHitted.png");
    Bullet playerBullet;

    //enemy 1
    Tank enemy1Tank(800, 600, 0.09f, "enemy.png", "enemyHitted.png");
    //Bullet enemy1bullet;

    sf::Texture mapTexture;
    map.setSize(sf::Vector2f(900, 800));
    mapTexture.loadFromFile("map.jpg");
    map.setTexture(&mapTexture);

    sf::Texture panelTexture;
    panel.setSize(sf::Vector2f(200, 800));
    panelTexture.loadFromFile("panel.png");
    panel.setTexture(&panelTexture);
    panel.setPosition(900, 0);
    //map.setPosition(100, 50);

    while (window.isOpen()) {
        sf::Event evnt;

        while (window.pollEvent(evnt)) {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
                /*case sf::Event::TextEntered:
                    if (evnt.text.unicode < 128) {
                        printf("%c", evnt.text.unicode);
                    }
                    break; */
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            playerTank.moveTop();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            playerTank.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            playerTank.moveBottom();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            playerTank.moveRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            playerBullet.shot(playerTank.getBulletDirection(), playerTank.body.getPosition().x, playerTank.body.getPosition().y);
        } 


        enemy1Tank.getHitted(playerBullet);
        playerBullet.updateBullet();
        enemy1Tank.getHittedAnimation();
        window.clear();
        window.draw(map);
        playerBullet.drawBullet(window);
        window.draw(playerTank.body);  
        window.draw(enemy1Tank.body);
        window.draw(panel);
        window.display();

    }

    return 0;
}