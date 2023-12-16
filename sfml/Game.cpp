#include "Game.h"
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
#include "GameSpeed.h"
#include "Wall.h"
#include "Brick.h"
#include "Box.h"
#include "BonusEvent.h"
#include "Mine.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


Game::Game() {
	tanksInGame = 3;
	bricksInGame = 30;
	boxesInGame = 30;
	wallsInGame = 30;
	gameSpeed = 2.0;

    loadTextures();
    gameStart();
}

void Game::gameStart() {
    sf::RenderWindow window(sf::VideoMode(1100, 800), "Tanks 2D", sf::Style::Close);
    window.setMouseCursorVisible(true);
    Tank playerTank(sf::Vector2f(450, 400), 1.6f * gameSpeed, 1);
    Bullet playerBullet;


    std::srand(std::time(0));
    sf::Clock clock;
    clock.restart();

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
                    for (int i = 0; i < tanksInGame; i++) {
                        enemyTanks.push_back(Tank(getRandomCordsForEnemySpawn(), 1.0f * gameSpeed, 0));
                        enemyBullets.push_back(Bullet());
                    }

                    for (int i = 0; i < wallsInGame; i++) {
                        walls.push_back(Wall(getRandomCordsForWalls()));
                    }

                    for (int i = 0; i < bricksInGame; i++) {
                        bricks.push_back(Brick(getRandomCordsForWalls()));
                    }

                    for (int i = 0; i < boxesInGame; i++) {
                        boxes.push_back(Box(getRandomCordsForWalls()));
                    }

                    startGame = true;
                    startGameTime();
                }

                if (mousePosition.x > tanksInGameIncrese.getGlobalBounds().left && mousePosition.x < tanksInGameIncrese.getGlobalBounds().left + tanksInGameIncrese.getGlobalBounds().width
                    && mousePosition.y > tanksInGameIncrese.getGlobalBounds().top && mousePosition.y < tanksInGameIncrese.getGlobalBounds().top + tanksInGameIncrese.getGlobalBounds().height) {
                    if (tanksInGame < 20) {
                        tanksInGame++;
                    }
                }

                if (mousePosition.x > tanksInGameDecrease.getGlobalBounds().left && mousePosition.x < tanksInGameDecrease.getGlobalBounds().left + tanksInGameDecrease.getGlobalBounds().width
                    && mousePosition.y > tanksInGameDecrease.getGlobalBounds().top && mousePosition.y < tanksInGameDecrease.getGlobalBounds().top + tanksInGameDecrease.getGlobalBounds().height) {
                    if (tanksInGame > 1) {
                        tanksInGame--;
                    }
                }
                if (mousePosition.x > bricksInGameIncrese.getGlobalBounds().left && mousePosition.x < bricksInGameIncrese.getGlobalBounds().left + bricksInGameIncrese.getGlobalBounds().width
                    && mousePosition.y > bricksInGameIncrese.getGlobalBounds().top && mousePosition.y < bricksInGameIncrese.getGlobalBounds().top + bricksInGameIncrese.getGlobalBounds().height) {
                    if (!disableInGameValues) {
                        bricksInGame++;
                    }
                }
                if (mousePosition.x > bricksInGameDecrease.getGlobalBounds().left && mousePosition.x < bricksInGameDecrease.getGlobalBounds().left + bricksInGameDecrease.getGlobalBounds().width
                    && mousePosition.y > bricksInGameDecrease.getGlobalBounds().top && mousePosition.y < bricksInGameDecrease.getGlobalBounds().top + bricksInGameDecrease.getGlobalBounds().height) {
                    if (bricksInGame > 0) {
                        bricksInGame--;
                    }
                }

                if (mousePosition.x > boxesInGameIncrease.getGlobalBounds().left && mousePosition.x < boxesInGameIncrease.getGlobalBounds().left + boxesInGameIncrease.getGlobalBounds().width
                    && mousePosition.y > boxesInGameIncrease.getGlobalBounds().top && mousePosition.y < boxesInGameIncrease.getGlobalBounds().top + boxesInGameIncrease.getGlobalBounds().height) {
                    if (!disableInGameValues) {
                        boxesInGame++;
                    }
                }
                
                if (mousePosition.x > boxesInGameDecrease.getGlobalBounds().left && mousePosition.x < boxesInGameDecrease.getGlobalBounds().left + boxesInGameDecrease.getGlobalBounds().width
                    && mousePosition.y > boxesInGameDecrease.getGlobalBounds().top && mousePosition.y < boxesInGameDecrease.getGlobalBounds().top + boxesInGameDecrease.getGlobalBounds().height) {
                    if (boxesInGame > 0) {
                        boxesInGame--;
                    }
                }

                if (mousePosition.x > wallsInGameIncrese.getGlobalBounds().left && mousePosition.x < wallsInGameIncrese.getGlobalBounds().left + wallsInGameIncrese.getGlobalBounds().width
                    && mousePosition.y > wallsInGameIncrese.getGlobalBounds().top && mousePosition.y < wallsInGameIncrese.getGlobalBounds().top + wallsInGameIncrese.getGlobalBounds().height) {
                    if (!disableInGameValues) {
                        wallsInGame++;
                    }
                }
                if (mousePosition.x > wallsInGameDecrease.getGlobalBounds().left && mousePosition.x < wallsInGameDecrease.getGlobalBounds().left + wallsInGameDecrease.getGlobalBounds().width
                    && mousePosition.y > wallsInGameDecrease.getGlobalBounds().top && mousePosition.y < wallsInGameDecrease.getGlobalBounds().top + wallsInGameDecrease.getGlobalBounds().height) {
                    if (wallsInGame > 0) {
                        wallsInGame--;
                    }
                }

                if (mousePosition.x > gameSpeedIncrese.getGlobalBounds().left && mousePosition.x < gameSpeedIncrese.getGlobalBounds().left + gameSpeedIncrese.getGlobalBounds().width
                    && mousePosition.y > gameSpeedIncrese.getGlobalBounds().top && mousePosition.y < gameSpeedIncrese.getGlobalBounds().top + gameSpeedIncrese.getGlobalBounds().height) {
                    if (gameSpeed < 4.9) {
                        gameSpeed = gameSpeed + 0.2;
                    }
                }

                if (mousePosition.x > gameSpeedDecrease.getGlobalBounds().left && mousePosition.x < gameSpeedDecrease.getGlobalBounds().left + gameSpeedDecrease.getGlobalBounds().width
                    && mousePosition.y > gameSpeedDecrease.getGlobalBounds().top && mousePosition.y < gameSpeedDecrease.getGlobalBounds().top + gameSpeedDecrease.getGlobalBounds().height) {
                    if (gameSpeed > 1.0) {
                        gameSpeed = gameSpeed - 0.2;
                    }
                }

                if (mousePosition.x > restartButton.getGlobalBounds().left && mousePosition.x < restartButton.getGlobalBounds().left + restartButton.getGlobalBounds().width
                    && mousePosition.y > restartButton.getGlobalBounds().top && mousePosition.y < restartButton.getGlobalBounds().top + restartButton.getGlobalBounds().height) {
                    displayEndScreen = false;
                    startGame = false;
                    playerTank.setHealthPoints(300);
                    playerTank.body.setPosition(sf::Vector2f(450, 400));
                    destroyedTanks = 0;

                    tanksInGame = 3;
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

            for (int i = 0; i < tanksInGame; i++) {
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

            for (int i = 0; i < bricksInGame; i++) {
                window.draw(bricks[i].body);
                for (int j = 0; j < enemyBullets.size(); j++) {
                    bricks[i].GetHitted(enemyBullets[j]);
                }
                bricks[i].GetHitted(playerBullet);
            }

            for (int i = 0; i < boxesInGame; i++) {
                window.draw(boxes[i].body);
                for (int j = 0; j < enemyBullets.size(); j++) {
                    boxes[i].GetHitted(enemyBullets[j]);
                }
                boxes[i].GetHitted(playerBullet);
            }

            for (int i = 0; i < wallsInGame; i++) {
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
            drawTextFloat(window, "Game speed: ", sf::Vector2f(260, 280), gameSpeed);
            drawText(window, "Enemy Tanks in game: ", sf::Vector2f(260, 320), tanksInGame);
            drawText(window, "Walls in game: ", sf::Vector2f(260, 360), wallsInGame);
            drawText(window, "Bricks in Game: ", sf::Vector2f(260, 400), bricksInGame);
            drawText(window, "Boxes in Game: ", sf::Vector2f(260, 440), boxesInGame);

            window.draw(tanksInGameIncrese);
            window.draw(tanksInGameDecrease);

            window.draw(bricksInGameIncrese);
            window.draw(bricksInGameDecrease);

            window.draw(boxesInGameIncrease);
            window.draw(boxesInGameDecrease);

            window.draw(wallsInGameIncrese);
            window.draw(wallsInGameDecrease);

            window.draw(gameSpeedIncrese);
            window.draw(gameSpeedDecrease);

            /*
            gameSpeed.drawIncrease(window);
            gameSpeed.drawDecrease(window);
            tanksInGame.drawIncrease(window);
            tanksInGame.drawDecrease(window);
            wallsInGame.drawIncrease(window);
            wallsInGame.drawDecrease(window);
            bricksInGame.drawIncrease(window);
            bricksInGame.drawDecrease(window);
            boxesInGame.drawIncrease(window);
            boxesInGame.drawDecrease(window);
            tanksInGame.SetTexture();

            */

            drawText(window, "Avaliable place: ", sf::Vector2f(260, 480), 120 - wallsInGame - bricksInGame - boxesInGame);

            if (wallsInGame + bricksInGame + boxesInGame > 119) {
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
            playerTank.setSpeed(1.6f * gameSpeed);
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
}

void Game::loadTextures() {
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
    mapTexture.loadFromFile("map.jpg");
    panelTexture.loadFromFile("panel.png");
    welcomeScreenTexture.loadFromFile("welcomeScreen.png");
    battleButtonTexture.loadFromFile("battleButton.png");
    restartButtonTexture.loadFromFile("restartButton.png");
    minusIconTexture.loadFromFile("minus.jpg");
    addIconTexture.loadFromFile("plus.jpg");

    map.setSize(sf::Vector2f(900, 800));
    map.setTexture(&mapTexture);

    panel.setSize(sf::Vector2f(200, 800));
    panel.setTexture(&panelTexture);
    panel.setPosition(900, 0);

    welcomeScreen.setSize(sf::Vector2f(500, 400));
    welcomeScreen.setTexture(&welcomeScreenTexture);
    welcomeScreen.setPosition(200, 200);

    battleButton.setSize(sf::Vector2f(120, 70));
    battleButton.setTexture(&battleButtonTexture);

    restartButton.setSize(sf::Vector2f(70, 70));
    restartButton.setTexture(&restartButtonTexture);

    tanksInGameIncrese.setTexture(&addIconTexture);
    tanksInGameIncrese.setPosition(sf::Vector2f(600, 320));
    tanksInGameIncrese.setSize(sf::Vector2f(25, 25));

    tanksInGameDecrease.setTexture(&minusIconTexture);
    tanksInGameDecrease.setPosition(sf::Vector2f(550, 320));
    tanksInGameDecrease.setSize(sf::Vector2f(25, 25));

    wallsInGameIncrese.setTexture(&addIconTexture);
    wallsInGameIncrese.setPosition(sf::Vector2f(600, 360));
    wallsInGameIncrese.setSize(sf::Vector2f(25, 25));

    wallsInGameDecrease.setTexture(&minusIconTexture);
    wallsInGameDecrease.setPosition(sf::Vector2f(550, 360));
    wallsInGameDecrease.setSize(sf::Vector2f(25, 25));

    bricksInGameIncrese.setTexture(&addIconTexture);
    bricksInGameIncrese.setPosition(sf::Vector2f(600, 400));
    bricksInGameIncrese.setSize(sf::Vector2f(25, 25));

    bricksInGameDecrease.setTexture(&minusIconTexture);
    bricksInGameDecrease.setPosition(sf::Vector2f(550, 400));
    bricksInGameDecrease.setSize(sf::Vector2f(25, 25));

    boxesInGameIncrease.setTexture(&addIconTexture);
    boxesInGameIncrease.setPosition(sf::Vector2f(600, 440));
    boxesInGameIncrease.setSize(sf::Vector2f(25, 25));

    boxesInGameDecrease.setTexture(&minusIconTexture);
    boxesInGameDecrease.setPosition(sf::Vector2f(550, 440));
    boxesInGameDecrease.setSize(sf::Vector2f(25, 25));


    gameSpeedIncrese.setTexture(&addIconTexture);
    gameSpeedIncrese.setPosition(sf::Vector2f(600, 280));
    gameSpeedIncrese.setSize(sf::Vector2f(25, 25));

    gameSpeedDecrease.setTexture(&minusIconTexture);
    gameSpeedDecrease.setPosition(sf::Vector2f(550, 280));
    gameSpeedDecrease.setSize(sf::Vector2f(25, 25));
}