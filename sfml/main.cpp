#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Bullet.h"
#include "EnemyTank.h"
#include "playerTank.h"
#include "StatsWindow.h"
#include "renderHelpers.h"
#include "globals.h"
#include "TanksInGame.h"
#include "WallsInGame.h"
#include "BricksInGame.h"
#include "BoxesInGame.h"
#include "Wall.h"
#include "Brick.h"
#include "Box.h"
#include "BonusEvent.h"
#include "Mine.h"
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
    sf::RectangleShape restartButton;
    bool mouseClicked = false;
    bool renderElements = false;
    bool disableInGameValues = false;
    bool startGame = false; 
    bool displayEndScreen = false;
    bool qKeyPressed = false;

    std::srand(std::time(0));
    sf::Clock clock;
    clock.restart();

    TanksInGame tanksInGame(sf::Vector2f(600, 350));
    WallsInGame wallsInGame(sf::Vector2f(600, 390));
    BricksInGame bricksInGame(sf::Vector2f(600, 430));
    BoxesInGame boxesInGame(sf::Vector2f(600, 470));

    texture1.loadFromFile("health.png");
    texture2.loadFromFile("dmg.png");
    texture3.loadFromFile("speed.png");
    texture4.loadFromFile("bombAdd.png");
    boxTexture.loadFromFile("box.png");
    brickTexture.loadFromFile("bricks.png");
    wallTexture.loadFromFile("wall.png");
    bomb.loadFromFile("bomb.png");
    playerTexture.loadFromFile("player.png");
    playerTextureHitted.loadFromFile("playerHitted.png");
    enemyTexture.loadFromFile("enemy.png");
    enemyTextureHitted.loadFromFile("enemyHitted.png");

    // player
    Tank playerTank(sf::Vector2f(450, 400), 3.0f, 1);
    Bullet playerBullet;

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

    sf::Texture restartButtonTexture;
    restartButton.setSize(sf::Vector2f(70, 70));
    restartButtonTexture.loadFromFile("restartButton.png");
    restartButton.setTexture(&restartButtonTexture);

    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left) {
            if (!mouseClicked) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (mousePosition.x > battleButton.getGlobalBounds().left && mousePosition.x < battleButton.getGlobalBounds().left + battleButton.getGlobalBounds().width
                    && mousePosition.y > battleButton.getGlobalBounds().top && mousePosition.y < battleButton.getGlobalBounds().top + battleButton.getGlobalBounds().height) {
                    drawText(window, "Loading...", sf::Vector2f(520, 540));
                    window.display();


                    std::vector<int> cordXarr = { 125, 175, 225, 275, 325, 375, 525, 575, 625, 675, 725, 775 };
                    std::vector<int> cordYarr = { 125, 175, 225, 275, 325, 475, 525, 575, 625, 675 };

                    for (int i = 0; i < cordXarr.size(); i++) {
                        for (int j = 0; j < cordYarr.size(); j++) {
                            availablePlace.push_back(sf::Vector2f(cordXarr[i], cordYarr[j]));
                        }
                    }
                    for (int i = 0; i < tanksInGame.tanksInGame; i++) {
                        enemyTanks.push_back(Tank(getRandomCordsForEnemySpawn(), 2.0f, 0));
                        enemyBullets.push_back(Bullet());
                    }

                    for (int i = 0; i < wallsInGame.wallsInGame; i++) {
                        walls.push_back(Wall(getRandomCordsForWalls()));
                    }

                    for (int i = 0; i < bricksInGame.bricksInGame; i++) {
                        bricks.push_back(Brick(getRandomCordsForWalls()));
                    }

                    for (int i = 0; i < boxesInGame.boxesInGame; i++) {
                        boxes.push_back(Box(getRandomCordsForWalls()));
                    }
                        
                    startGame = true; 
                    startGameTime();
                }

                if (mousePosition.x > tanksInGame.bodyIncrease.getGlobalBounds().left && mousePosition.x < tanksInGame.bodyIncrease.getGlobalBounds().left + tanksInGame.bodyIncrease.getGlobalBounds().width
                    && mousePosition.y > tanksInGame.bodyIncrease.getGlobalBounds().top && mousePosition.y < tanksInGame.bodyIncrease.getGlobalBounds().top + tanksInGame.bodyIncrease.getGlobalBounds().height) {
                    tanksInGame.IncreaseValue();
                        
                }
                if (mousePosition.x > tanksInGame.bodyDecrease.getGlobalBounds().left && mousePosition.x < tanksInGame.bodyDecrease.getGlobalBounds().left + tanksInGame.bodyDecrease.getGlobalBounds().width
                    && mousePosition.y > tanksInGame.bodyDecrease.getGlobalBounds().top && mousePosition.y < tanksInGame.bodyDecrease.getGlobalBounds().top + tanksInGame.bodyDecrease.getGlobalBounds().height) {
                    tanksInGame.DecreaseValue();
                }

                if (mousePosition.x > wallsInGame.bodyIncrease.getGlobalBounds().left && mousePosition.x < wallsInGame.bodyIncrease.getGlobalBounds().left + wallsInGame.bodyIncrease.getGlobalBounds().width
                    && mousePosition.y > wallsInGame.bodyIncrease.getGlobalBounds().top && mousePosition.y < wallsInGame.bodyIncrease.getGlobalBounds().top + wallsInGame.bodyIncrease.getGlobalBounds().height) {
                    if (!disableInGameValues) {
                        wallsInGame.IncreaseValue();
                    }
                }
                if (mousePosition.x > wallsInGame.bodyDecrease.getGlobalBounds().left && mousePosition.x < wallsInGame.bodyDecrease.getGlobalBounds().left + wallsInGame.bodyDecrease.getGlobalBounds().width
                    && mousePosition.y > wallsInGame.bodyDecrease.getGlobalBounds().top && mousePosition.y < wallsInGame.bodyDecrease.getGlobalBounds().top + wallsInGame.bodyDecrease.getGlobalBounds().height) {
                    wallsInGame.DecreaseValue();
                }

                if (mousePosition.x > bricksInGame.bodyIncrease.getGlobalBounds().left && mousePosition.x < bricksInGame.bodyIncrease.getGlobalBounds().left + bricksInGame.bodyIncrease.getGlobalBounds().width
                    && mousePosition.y > bricksInGame.bodyIncrease.getGlobalBounds().top && mousePosition.y < bricksInGame.bodyIncrease.getGlobalBounds().top + bricksInGame.bodyIncrease.getGlobalBounds().height) {
                    if (!disableInGameValues) {
                        bricksInGame.IncreaseValue();
                    }
                }
                if (mousePosition.x > bricksInGame.bodyDecrease.getGlobalBounds().left && mousePosition.x < bricksInGame.bodyDecrease.getGlobalBounds().left + bricksInGame.bodyDecrease.getGlobalBounds().width
                    && mousePosition.y > bricksInGame.bodyDecrease.getGlobalBounds().top && mousePosition.y < bricksInGame.bodyDecrease.getGlobalBounds().top + bricksInGame.bodyDecrease.getGlobalBounds().height) {
                    bricksInGame.DecreaseValue();
                }

                if (mousePosition.x > boxesInGame.bodyIncrease.getGlobalBounds().left && mousePosition.x < boxesInGame.bodyIncrease.getGlobalBounds().left + boxesInGame.bodyIncrease.getGlobalBounds().width
                    && mousePosition.y > boxesInGame.bodyIncrease.getGlobalBounds().top && mousePosition.y < boxesInGame.bodyIncrease.getGlobalBounds().top + boxesInGame.bodyIncrease.getGlobalBounds().height) {
                    if (!disableInGameValues) {
                        boxesInGame.IncreaseValue();
                    }
                }
                if (mousePosition.x > boxesInGame.bodyDecrease.getGlobalBounds().left && mousePosition.x < boxesInGame.bodyDecrease.getGlobalBounds().left + boxesInGame.bodyDecrease.getGlobalBounds().width
                    && mousePosition.y > boxesInGame.bodyDecrease.getGlobalBounds().top && mousePosition.y < boxesInGame.bodyDecrease.getGlobalBounds().top + boxesInGame.bodyDecrease.getGlobalBounds().height) {
                    boxesInGame.DecreaseValue();
                }

                if (mousePosition.x > restartButton.getGlobalBounds().left && mousePosition.x < restartButton.getGlobalBounds().left + restartButton.getGlobalBounds().width
                    && mousePosition.y > restartButton.getGlobalBounds().top && mousePosition.y < restartButton.getGlobalBounds().top + restartButton.getGlobalBounds().height) {
                    displayEndScreen = false;
                    startGame = false;
                    playerTank.setHealthPoints(300);
                    playerTank.body.setPosition(sf::Vector2f(450, 400));
                    destroyedTanks = 0;

                    walls.clear();
                    bricks.clear();
                    boxes.clear(); 
                    enemyTanks.clear(); 
                    enemyBullets.clear(); 
                    availablePlace.clear(); 
                    bonusEvents.clear();
                    minesOnMap.clear();
                }
            }
            mouseClicked = true;
        }

        if (evnt.type == sf::Event::MouseButtonReleased && evnt.mouseButton.button == sf::Mouse::Left) {
            mouseClicked = false;
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
            playerBullet.shot(playerTank.getBulletDirection(), playerTank.body.getPosition().x, playerTank.body.getPosition().y, playerTank.getDamage());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            if (!qKeyPressed) {  
                if (playerTank.getMines() > 0) {
                    minesOnMap.push_back(Mine(playerTank.body.getPosition()));
                    playerTank.useOneMine();
                }
                qKeyPressed = true;  
            }
        }
        else {
            qKeyPressed = false;  
        }

        countGameTime();
        window.clear();
        window.draw(map);

        if (startGame) {
            for (int i = 0; i < minesOnMap.size(); i++) {
                window.draw(minesOnMap[i].body);
            }

            playerBullet.drawBullet(window);
            window.draw(playerTank.body);
            playerTank.eventBonusIntersects();

            for (int i = 0; i < tanksInGame.tanksInGame; i++) {
                enemyTanks[i].getHitted(playerBullet);
                enemyTanks[i].getHittedAnimation();
                playerTank.getHitted(enemyBullets[i]);
                enemyBullets[i].drawBullet(window);
                enemyBullets[i].updateBullet();
                enemyTanks[i].drawTank(window);
                enemyTanks[i].enemyIntelligence(playerTank, enemyBullets[i], clock);
                enemyTanks[i].respawnEnemy();
                enemyTanks[i].eventBonusIntersects();
                enemyTanks[i].mineIntersects();
            }

            for (int i = 0; i < bricksInGame.bricksInGame; i++) {
                window.draw(bricks[i].body);
                for (int j = 0; j < enemyBullets.size(); j++) {
                    bricks[i].GetHitted(enemyBullets[j]);
                }
                bricks[i].GetHitted(playerBullet);
            }

            for (int i = 0; i < boxesInGame.boxesInGame; i++) {
                window.draw(boxes[i].body);
                for (int j = 0; j < enemyBullets.size(); j++) {
                    boxes[i].GetHitted(enemyBullets[j]);
                }
                boxes[i].GetHitted(playerBullet);
            }

            for (int i = 0; i < wallsInGame.wallsInGame; i++) {
                window.draw(walls[i].body);
                for (int j = 0; j < enemyBullets.size(); j++) {
                    walls[i].GetHitted(enemyBullets[j]);
                }
                walls[i].GetHitted(playerBullet);
            }

            for (int i = 0; i < bonusEvents.size(); i++) {
                bonusEvents[i].drawEvent(window);
            }
        }
        else {
            window.draw(welcomeScreen);
            restartButton.setPosition(0, 0);
            battleButton.setPosition(405, 500);
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
            else {
                disableInGameValues = false;
            }
        }

        if (playerTank.getHealthPoints() <= 0) {
            stopGameTime();
            playerTank.setHealthPoints(0);
            playerTank.setDamage(100);
            playerTank.setSpeed(3.0);
            playerTank.setMines(3);
            playerTank.body.setPosition(-2000, -2000);
           
            displayEndScreen = true;
        }

        if (displayEndScreen) {
            window.draw(welcomeScreen);
            restartButton.setPosition(425, 500);
            battleButton.setPosition(0, 0);
            window.draw(restartButton);

            int minutes = gameTime / 60;
            int seconds = gameTime % 60;

            drawText(window, "Game over", sf::Vector2f(400, 300));
            drawText(window, "Points: ", sf::Vector2f(350, 340), gameTime + ((destroyedTanks - 1) * 15));
            drawText(window, "Game time: ", sf::Vector2f(350, 380), minutes);
            if (seconds < 10) {
                drawText(window, ": 0", sf::Vector2f(470, 380), seconds);
            }
            else {
                drawText(window, ": ", sf::Vector2f(470, 380), seconds);
            }
            drawText(window, "Destroyed enemies: ", sf::Vector2f(350, 420), destroyedTanks - 1);

            drawText(window, "Tanks 2D", sf::Vector2f(240, 240));
        }
        
        playerBullet.updateBullet();
        playerTank.getHittedAnimation();
        window.draw(panel);
        drawText(window, "Kills: ", sf::Vector2f(950, 200), destroyedTanks);
        drawText(window, "Game time: ", sf::Vector2f(950, 300), gameTime);
        drawText(window, "Hit points: ", sf::Vector2f(950, 400), playerTank.getHealthPoints());
        drawText(window, "Damage: ", sf::Vector2f(950, 500), playerTank.getDamage());
        if (playerTank.getSpeed() == 5.0f) {
            drawText(window, "Max speed", sf::Vector2f(950, 600));
        }
        else {
            drawText(window, "Speed: ", sf::Vector2f(950, 600), playerTank.getSpeed());
        }
        drawText(window, "Mines: ", sf::Vector2f(950, 700), playerTank.getMines());
        drawText(window, "Q to place", sf::Vector2f(950, 730));

        window.display();
    }
    return 0;
}