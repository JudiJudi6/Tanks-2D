#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Bullet.h"
#include "EnemyTank.h"
#include "playerTank.h"
#include "StatsWindow.h"
#include "renderHelpers.h"
#include "enemyIntelligence.h"
#include "TanksInGame.h"
#include "WallsInGame.h"
#include "BricksInGame.h"
#include "BoxesInGame.h"
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
    bool renderElements = false;
    bool disableInGameValues = false;

    bool startGame = false; 
   // sf::Texture texture;
    //texture.loadFromFile("enemy.png");
    
    std::srand(std::time(0));
    sf::Clock clock;
    clock.restart();

    std::vector<int> cordXarr = { 125, 175, 225, 275, 325, 375, 525, 575, 625, 675, 725, 775 };
    std::vector<int> cordYarr = { 125, 175, 225, 275, 325, 475, 525, 575, 625, 675 };

    for (int i = 0; i < cordXarr.size(); i++) {
        for (int j = 0; j < cordYarr.size(); j++) {
            availablePlace.push_back(sf::Vector2f(cordXarr[i], cordYarr[j]));
        }
    }
   // int newDirection = std::rand() % 4;
    //sf::Clock clock;
    //clock.restart();

  //  int tanksInGame = 3;
    TanksInGame tanksInGame(sf::Vector2f(600, 350));
    WallsInGame wallsInGame(sf::Vector2f(600, 390));
    BricksInGame bricksInGame(sf::Vector2f(600, 430));
    BoxesInGame boxesInGame(sf::Vector2f(600, 470));

  //  int wallsInGame = 0;
    //int bricksInGame = 0;
    //int boxesInGame = 10;

    //stats
    //sf::Text killsCounter;
    //int destroyedTanks = 0;

    // Gracz
    Tank playerTank(sf::Vector2f(450, 400), 5.0f, "player.png", "playerHitted.png");
    Bullet playerBullet;

   // enemyTanks.push_back(Tank(getRandomCordsForEnemySpawn(), 0.9f, "enemy.png", "enemyHitted.png"));

    
    


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
                        drawText(window, "Loading...", sf::Vector2f(520, 540));
                        window.display();
                        for (int i = 0; i < tanksInGame.tanksInGame; i++) {
                            enemyTanks.push_back(Tank(getRandomCordsForEnemySpawn(), 1.5f, "enemy.png", "enemyHitted.png"));
                            enemyBullets.push_back(Bullet());
                            // std::cout << enemyTanks.size();
                        }

                        for (int i = 0; i < wallsInGame.wallsInGame; i++) {
                            walls.push_back(Wall(getRandomCordsForWalls(), "wall.png"));
                        }

                        for (int i = 0; i < bricksInGame.bricksInGame; i++) {
                            bricks.push_back(Brick(getRandomCordsForWalls(), "Bricks.png"));
                        }

                        for (int i = 0; i < boxesInGame.boxesInGame; i++) {
                            boxes.push_back(Box(getRandomCordsForWalls(), "box.png"));
                        }
                        startGame = true; 
                    }

                    if (mousePosition.x > tanksInGame.bodyIncrease.getGlobalBounds().left && mousePosition.x < tanksInGame.bodyIncrease.getGlobalBounds().left + tanksInGame.bodyIncrease.getGlobalBounds().width
                        && mousePosition.y > tanksInGame.bodyIncrease.getGlobalBounds().top && mousePosition.y < tanksInGame.bodyIncrease.getGlobalBounds().top + tanksInGame.bodyIncrease.getGlobalBounds().height) {
                        //std::cout << "1";
                        tanksInGame.IncreaseValue();
                        
                    }
                    if (mousePosition.x > tanksInGame.bodyDecrease.getGlobalBounds().left && mousePosition.x < tanksInGame.bodyDecrease.getGlobalBounds().left + tanksInGame.bodyDecrease.getGlobalBounds().width
                        && mousePosition.y > tanksInGame.bodyDecrease.getGlobalBounds().top && mousePosition.y < tanksInGame.bodyDecrease.getGlobalBounds().top + tanksInGame.bodyDecrease.getGlobalBounds().height) {
                       // std::cout << "2";
                        tanksInGame.DecreaseValue();
                    }

                    if (mousePosition.x > wallsInGame.bodyIncrease.getGlobalBounds().left && mousePosition.x < wallsInGame.bodyIncrease.getGlobalBounds().left + wallsInGame.bodyIncrease.getGlobalBounds().width
                        && mousePosition.y > wallsInGame.bodyIncrease.getGlobalBounds().top && mousePosition.y < wallsInGame.bodyIncrease.getGlobalBounds().top + wallsInGame.bodyIncrease.getGlobalBounds().height) {
                       //std::cout << "1";
                        if (!disableInGameValues) {
                            wallsInGame.IncreaseValue();
                        }
                    }
                    if (mousePosition.x > wallsInGame.bodyDecrease.getGlobalBounds().left && mousePosition.x < wallsInGame.bodyDecrease.getGlobalBounds().left + wallsInGame.bodyDecrease.getGlobalBounds().width
                        && mousePosition.y > wallsInGame.bodyDecrease.getGlobalBounds().top && mousePosition.y < wallsInGame.bodyDecrease.getGlobalBounds().top + wallsInGame.bodyDecrease.getGlobalBounds().height) {
                       // std::cout << "2";
                        wallsInGame.DecreaseValue();
                    }

                    if (mousePosition.x > bricksInGame.bodyIncrease.getGlobalBounds().left && mousePosition.x < bricksInGame.bodyIncrease.getGlobalBounds().left + bricksInGame.bodyIncrease.getGlobalBounds().width
                        && mousePosition.y > bricksInGame.bodyIncrease.getGlobalBounds().top && mousePosition.y < bricksInGame.bodyIncrease.getGlobalBounds().top + bricksInGame.bodyIncrease.getGlobalBounds().height) {
                        //std::cout << "1";
                        if (!disableInGameValues) {
                            bricksInGame.IncreaseValue();
                        }
                    }
                    if (mousePosition.x > bricksInGame.bodyDecrease.getGlobalBounds().left && mousePosition.x < bricksInGame.bodyDecrease.getGlobalBounds().left + bricksInGame.bodyDecrease.getGlobalBounds().width
                        && mousePosition.y > bricksInGame.bodyDecrease.getGlobalBounds().top && mousePosition.y < bricksInGame.bodyDecrease.getGlobalBounds().top + bricksInGame.bodyDecrease.getGlobalBounds().height) {
                      //  std::cout << "2";
                        bricksInGame.DecreaseValue();
                    }

                    if (mousePosition.x > boxesInGame.bodyIncrease.getGlobalBounds().left && mousePosition.x < boxesInGame.bodyIncrease.getGlobalBounds().left + boxesInGame.bodyIncrease.getGlobalBounds().width
                        && mousePosition.y > boxesInGame.bodyIncrease.getGlobalBounds().top && mousePosition.y < boxesInGame.bodyIncrease.getGlobalBounds().top + boxesInGame.bodyIncrease.getGlobalBounds().height) {
                        //std::cout << "1";
                        if (!disableInGameValues) {
                            boxesInGame.IncreaseValue();
                        }
                    }
                    if (mousePosition.x > boxesInGame.bodyDecrease.getGlobalBounds().left && mousePosition.x < boxesInGame.bodyDecrease.getGlobalBounds().left + boxesInGame.bodyDecrease.getGlobalBounds().width
                        && mousePosition.y > boxesInGame.bodyDecrease.getGlobalBounds().top && mousePosition.y < boxesInGame.bodyDecrease.getGlobalBounds().top + boxesInGame.bodyDecrease.getGlobalBounds().height) {
                       // std::cout << "2";
                        boxesInGame.DecreaseValue();
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

        if (!renderElements) {

            renderElements = true;
        }


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

            for (int i = 0; i < bricksInGame.bricksInGame; i++) {
                window.draw(bricks[i].body);
                bricks[i].SetWallTexture();
                for (int j = 0; j < enemyBullets.size(); j++) {
                    bricks[i].GetHitted(enemyBullets[j]);
                }
                bricks[i].GetHitted(playerBullet);
            }

            for (int i = 0; i < boxesInGame.boxesInGame; i++) {
                window.draw(boxes[i].body);
                boxes[i].SetWallTexture();
                for (int j = 0; j < enemyBullets.size(); j++) {
                    boxes[i].GetHitted(enemyBullets[j]);
                }
                boxes[i].GetHitted(playerBullet);
            }

            for (int i = 0; i < wallsInGame.wallsInGame; i++) {
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
            drawText(window, "Walls in game: ", sf::Vector2f(260, 360), wallsInGame.wallsInGame);
            drawText(window, "Bricks in Game: ", sf::Vector2f(260, 400), bricksInGame.bricksInGame);
            drawText(window, "Boxes in Game: ", sf::Vector2f(260, 440), boxesInGame.boxesInGame);

            tanksInGame.drawIncrease(window);
            tanksInGame.drawDecrease(window);
            wallsInGame.drawIncrease(window);
            wallsInGame.drawDecrease(window);
            bricksInGame.drawIncrease(window);
            bricksInGame.drawDecrease(window);
            boxesInGame.drawIncrease(window);
            boxesInGame.drawDecrease(window);
            tanksInGame.SetTexture();


            drawText(window, "Avaliable place: ", sf::Vector2f(260, 480), 120 - wallsInGame.wallsInGame - bricksInGame.bricksInGame - boxesInGame.boxesInGame);
            
            if (wallsInGame.wallsInGame + bricksInGame.bricksInGame + boxesInGame.boxesInGame > 119) {
                disableInGameValues = true;
            }
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