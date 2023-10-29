#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Bullet.h"
#include "EnemyTank.h"
#include "playerTank.h"
#include "StatsWindow.h"
#include "renderHelpers.h"
#include "enemyIntelligence.h"
#include "TanksInGame.h"
#include "Wall.h"
#include "Brick.h"
#include "Box.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1100, 800), "Tanks 2D", sf::Style::Close);
    window.setMouseCursorVisible(true);
    sf::RectangleShape map;
    sf::RectangleShape panel;
    sf::RectangleShape welcomeScreen;
    sf::RectangleShape battleButton;
    bool mouseClicked = false;

    bool startGame = false; 
   // sf::Texture texture;
    //texture.loadFromFile("enemy.png");
    
    std::srand(std::time(0));
    sf::Clock clock;
    clock.restart();
   // int newDirection = std::rand() % 4;
    //sf::Clock clock;
    //clock.restart();

  //  int tanksInGame = 3;
    TanksInGame tanksInGame(sf::Vector2f(600, 350));

    int wallsInGame = 2;
    int bricksInGame = 35;
    int boxesInGame = 15;

    //stats
    //sf::Text killsCounter;
    //int destroyedTanks = 0;

    // Gracz
    Tank playerTank(sf::Vector2f(450, 400), 5.0f, "player.png", "playerHitted.png");
    Bullet playerBullet;

   // enemyTanks.push_back(Tank(getRandomCordsForEnemySpawn(), 0.9f, "enemy.png", "enemyHitted.png"));

    for (int i = 0; i < tanksInGame.tanksInGame; i++) {
        enemyTanks.push_back(Tank(getRandomCordsForEnemySpawn(), 1.5f, "enemy.png", "enemyHitted.png"));
        enemyBullets.push_back(Bullet());
        // std::cout << enemyTanks.size();
    }

    for (int i = 0; i < wallsInGame; i++) {
        walls.push_back(Wall(getRandomCordsForWalls(), "wall.png"));
    }

    for (int i = 0; i < bricksInGame; i++) {
        bricks.push_back(Brick(getRandomCordsForWalls(), "Bricks.png"));
    }

    for (int i = 0; i < boxesInGame; i++) {
        boxes.push_back(Box(getRandomCordsForWalls(), "box.png"));
    }
    


    sf::Texture mapTexture;
    map.setSize(sf::Vector2f(900, 800));
    mapTexture.loadFromFile("map.jpg");
    map.setTexture(&mapTexture);

    sf::Texture panelTexture;
    panel.setSize(sf::Vector2f(200, 800));
    panelTexture.loadFromFile("panel.png");
    panel.setTexture(&panelTexture);
    panel.setPosition(900, 0);

    sf::Texture welcomeScreenTexture;
    welcomeScreen.setSize(sf::Vector2f(500, 400));
    welcomeScreenTexture.loadFromFile("welcomeScreen.png");
    welcomeScreen.setTexture(&welcomeScreenTexture);
    welcomeScreen.setPosition(200, 200);

    sf::Texture battleButtonTexture;
    battleButton.setSize(sf::Vector2f(120, 70));
    battleButtonTexture.loadFromFile("battleButton.png");
    battleButton.setTexture(&battleButtonTexture);
    battleButton.setPosition(405, 500);

    //Stats gameStats;

    startGameTime();


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

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        if (!startGame) {
            if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left) {
                if (!mouseClicked) {
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    if (mousePosition.x > battleButton.getGlobalBounds().left && mousePosition.x < battleButton.getGlobalBounds().left + battleButton.getGlobalBounds().width
                        && mousePosition.y > battleButton.getGlobalBounds().top && mousePosition.y < battleButton.getGlobalBounds().top + battleButton.getGlobalBounds().height) {
                        ///std::cout << "dsa";
                        startGame = true;
                    }
                    if (mousePosition.x > tanksInGame.bodyIncrease.getGlobalBounds().left && mousePosition.x < tanksInGame.bodyIncrease.getGlobalBounds().left + tanksInGame.bodyIncrease.getGlobalBounds().width
                        && mousePosition.y > tanksInGame.bodyIncrease.getGlobalBounds().top && mousePosition.y < tanksInGame.bodyIncrease.getGlobalBounds().top + tanksInGame.bodyIncrease.getGlobalBounds().height) {
                        std::cout << "1";
                        tanksInGame.IncreaseValue();
                    }
                    if (mousePosition.x > tanksInGame.bodyDecrease.getGlobalBounds().left && mousePosition.x < tanksInGame.bodyDecrease.getGlobalBounds().left + tanksInGame.bodyDecrease.getGlobalBounds().width
                        && mousePosition.y > tanksInGame.bodyDecrease.getGlobalBounds().top && mousePosition.y < tanksInGame.bodyDecrease.getGlobalBounds().top + tanksInGame.bodyDecrease.getGlobalBounds().height) {
                        std::cout << "2";
                        tanksInGame.DecreaseValue();
                    }
                }
                mouseClicked = true;
            }

            if (evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Left) {
                mouseClicked = false;
            }

        }
        else {
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

            countGameTime();
        }

       

        window.clear();
        window.draw(map);
        /*
        window.draw(enemy1Tank.body);
        window.draw(enemy2Tank.body);
        window.draw(enemy3Tank.body);
        */


        if (startGame) {

            playerBullet.drawBullet(window);
          // playerTank.body.setPosition(sf::Vector2f(450, 400));
            window.draw(playerTank.body);

            for (int i = 0; i < tanksInGame.tanksInGame; i++) {
                enemyTanks[i].getHitted(playerBullet);
                enemyTanks[i].getHittedAnimation();
                playerTank.getHitted(enemyBullets[i]);
                enemyBullets[i].drawBullet(window);
                enemyBullets[i].updateBullet();
                enemyTanks[i].drawTank(window);
                enemyTanks[i].enemyIntelligence(playerTank, enemyBullets[i], clock);
                enemyTanks[i].respawnEnemy();
            }

            for (int i = 0; i < bricksInGame; i++) {
                window.draw(bricks[i].body);
                bricks[i].SetWallTexture();
                for (int j = 0; j < enemyBullets.size(); j++) {
                    bricks[i].GetHitted(enemyBullets[j]);
                }
                bricks[i].GetHitted(playerBullet);
            }

            for (int i = 0; i < boxesInGame; i++) {
                window.draw(boxes[i].body);
                boxes[i].SetWallTexture();
                for (int j = 0; j < enemyBullets.size(); j++) {
                    boxes[i].GetHitted(enemyBullets[j]);
                }
                boxes[i].GetHitted(playerBullet);
            }

            for (int i = 0; i < wallsInGame; i++) {
                window.draw(walls[i].body);
                walls[i].SetWallTexture();
                for (int j = 0; j < enemyBullets.size(); j++) {
                    walls[i].GetHitted(enemyBullets[j]);
                }
                walls[i].GetHitted(playerBullet);
            }
        }
        else {
            window.draw(welcomeScreen);
            window.draw(battleButton);
            drawText(window, "Tanks 2D", sf::Vector2f(240, 240));
            drawText(window, "Enemy Tanks in game: " ,sf::Vector2f(260, 320), tanksInGame.tanksInGame);
            drawText(window, "Walls in game: ", sf::Vector2f(260, 360), wallsInGame);
            drawText(window, "Bricks in Game: ", sf::Vector2f(260, 400), bricksInGame);
            drawText(window, "Boxes in Game: ", sf::Vector2f(260, 440), boxesInGame);

            tanksInGame.drawIncrease(window);
            tanksInGame.drawDecrease(window);
            tanksInGame.SetTexture();

        }
        playerBullet.updateBullet();
        playerTank.getHittedAnimation();
        window.draw(panel);
        
        //draw stats
        //std::cout << destroyedTanks;
        drawText(window, "Kills: ", sf::Vector2f(950, 200), destroyedTanks);
        drawText(window, "Game time: ", sf::Vector2f(950, 300), gameTime);
        drawText(window, "Player HP: ", sf::Vector2f(950, 400), playerTank.getHealthPoints());


        //addKill();

        window.display();

    }

    return 0;
}