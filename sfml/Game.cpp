#include "Game.h"
#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Bullet.h"
#include "renderHelpers.h"
#include "Wall.h"
#include "Brick.h"
#include "Box.h"
#include "BonusEvent.h"
#include "Mine.h"
#include "StatsWindow.h"


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
                    
                    if (mapOption == 0) {
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
                            walls.push_back(Wall(getRandomCordsForWalls(), &wallTexture));
                        }

                        for (int i = 0; i < bricksInGame; i++) {
                            bricks.push_back(Brick(getRandomCordsForWalls(), &brickTexture));
                        }

                        for (int i = 0; i < boxesInGame; i++) {
                            boxes.push_back(Box(getRandomCordsForWalls(), &boxTexture));
                        }
                    }
                    else if (mapOption == 1) {
                        std::vector<sf::Vector2f> wallCoords = {
                            {125,125}, {175,125}, {225,125}, {275,125}, {625,125}, {675,125}, {725,125}, {775,125},
                            {125,175}, {775,175}, {125,225}, {775,225}, {125,275}, {275, 275}, {625,275}, {775,275},
                            {125,525}, {275,525}, {625,525}, {775,525}, {125,575}, {775,575},  {125,625}, {775,625},
                            {125,675}, {175,675}, {225,675}, {275,675}, {625,675}, {675,675}, {725,675}, {775,675}
                        };

                        std::vector<sf::Vector2f> brickCoords = {
                            {275,175}, {625,175}, {275,225}, {625,225}, {175,275}, {225,275}, {675,275}, {725,275},
                            {175,525}, {225,525}, {675,525}, {725,525}, {275,575}, {625,575}, {275,625}, {625,625}
                        };

                        std::vector<sf::Vector2f> boxCoords = {
                            {175,175}, {225,175}, {175,225}, {225,225}, {675,175}, {725,175}, {675,225}, {725,225},
                            {175,575}, {225,575}, {175,625}, {225,625}, {675,575}, {725,575}, {675, 625}, {725,625}
                        };

                        tanksInGame = 3;
                        wallsInGame = wallCoords.size();
                        bricksInGame = brickCoords.size();
                        boxesInGame = boxCoords.size();

                        for (const auto& coords : wallCoords) {
                            walls.push_back(Wall(coords, &wallTexture));
                        }

                        for (const auto& coords : brickCoords) {
                            bricks.push_back(Brick(coords, &brickTexture));
                        }

                        for (const auto& coords : boxCoords) {
                            boxes.push_back(Box(coords, &boxTexture));
                        }

                        for (int i = 0; i < tanksInGame; i++) {
                            enemyTanks.push_back(Tank(getRandomCordsForEnemySpawn(), 1.0f * gameSpeed, 0));
                            enemyBullets.push_back(Bullet());
                        }
                    }
                    else if (mapOption == 2) {
                        std::vector<sf::Vector2f> wallCoords = {
                            {125,125}, {175,125}, {225,125}, {275,125}, {325,125}, {375,125}, {525,125}, {575,125}, {625,125}, {675,125}, {725,125}, {775,125},
                            {125,175}, {775,175},
                            {125,225}, {775,225},
                            {125,275}, {775,275},
                            {125,325}, {775,325},

                            {125,475}, {775,475},
                            {125,525}, {775,525},
                            {125,575}, {775,575},
                            {125,625}, {775,625},
                            {125,675}, {175,675}, {225,675}, {275,675}, {325,675}, {375,675}, {525,675}, {575,675}, {625,675}, {675,675}, {725,675}, {775,675},
                        };

                        std::vector<sf::Vector2f> brickCoords = {
                            {325,175}, {575,175},
                            {275,225}, {625,225},
                            {225,275}, {675,275},
                            {175,325}, {725,325},

                            {175,475}, {725,475},
                            {225,525}, {675,525},
                            {275,575}, {625,575},
                            {325,625}, {575,625},
                        };

                        std::vector<sf::Vector2f> boxCoords = {
                            {175,175}, {225,175}, {275,175}, {625,175}, {675,175}, {725,175},
                            {175,225}, {225,225}, {675,225}, {725,225},
                            {175,275}, {375,275}, {525,275}, {725,275},
                            {325,325}, {375,325}, {525,325}, {575,325},

                            {325,475}, {375,475}, {525,475}, {575,475},
                            {175,525}, {375,525}, {525,525}, {725,525},
                            {175,575}, {225,575}, {675,575}, {725,575},
                            {175,625}, {225,625}, {275,625}, {625,625}, {675,625}, {725,625},
                        };

                        tanksInGame = 5;
                        wallsInGame = wallCoords.size();
                        bricksInGame = brickCoords.size();
                        boxesInGame = boxCoords.size();

                        for (const auto& coords : wallCoords) {
                            walls.push_back(Wall(coords, &wallTexture));
                        }

                        for (const auto& coords : brickCoords) {
                            bricks.push_back(Brick(coords, &brickTexture));
                        }

                        for (const auto& coords : boxCoords) {
                            boxes.push_back(Box(coords, &boxTexture));
                        }

                        for (int i = 0; i < tanksInGame; i++) {
                            enemyTanks.push_back(Tank(getRandomCordsForEnemySpawn(), 1.0f * gameSpeed, 0));
                            enemyBullets.push_back(Bullet());
                        }
                    }
                    else if (mapOption == 3) {
                        std::vector<sf::Vector2f> wallCoords = {
                            {125, 125}, {175,125}, {225,125}, {675, 125}, {725,125}, {775,125},
                            {125,175}, {775,175},
                            {125,225}, {375,225}, {525,225}, {775,225},
                            {375,275}, {525,275},
                            {275,325}, {325,325}, {375,325}, {525, 325}, {575,325}, {625,325},

                            {275,475}, {325,475}, {375,475}, {525, 475}, {575,475}, {625,475},
                            {375,525}, {525, 525},
                            {125,575}, {375,575}, {525,575}, {775,575},
                            {125,625}, {775,625},
                            {125, 675}, {175,675}, {225,675}, {675, 675}, {725,675}, {775,675},
                        };

                        std::vector<sf::Vector2f> brickCoords = {
                            {225,175}, {675,175},
                            {175,225}, {325,225}, {575,225}, {725,225},
                            {275,275}, {625,275},
                            {275,525}, {625,525},
                            {175,575}, {325,575}, {575,575}, {725,575},
                            {225,625}, {675,625},
                        };

                        std::vector<sf::Vector2f> boxCoords = {
                            {275,125}, {625,125},
                            {175,175}, {375,175}, {525,175}, {725,175},
                            {125,275}, {325,275}, {575,275}, {775,275},
                            {225,325}, {675,325},
                            {225,475}, {675,475},
                            {125,525}, {325,525}, {575,525}, {775,525},
                            {175,625}, {375,625}, {525,625}, {725,625},
                            {275,675}, {625,675},
                        };

                        tanksInGame = 8;
                        wallsInGame = wallCoords.size();
                        bricksInGame = brickCoords.size();
                        boxesInGame = boxCoords.size();

                        for (const auto& coords : wallCoords) {
                            walls.push_back(Wall(coords, &wallTexture));
                        }

                        for (const auto& coords : brickCoords) {
                            bricks.push_back(Brick(coords, &brickTexture));
                        }

                        for (const auto& coords : boxCoords) {
                            boxes.push_back(Box(coords, &boxTexture));
                        }

                        for (int i = 0; i < tanksInGame; i++) {
                            enemyTanks.push_back(Tank(getRandomCordsForEnemySpawn(), 1.0f * gameSpeed, 0));
                            enemyBullets.push_back(Bullet());
                        }
                        }
                    else if (mapOption == 4) {
                        std::vector<sf::Vector2f> wallCoords = {
                            {125,125}, {175,125}, {225,125}, {325,125}, {375,125}, {525,125}, {575,125}, {675,125}, {725,125}, {775,125},
                            {375,175}, {525,175}, {125,225}, {775,225}, {375,275}, {525,275}, 
                            {125,325}, {175,325}, {225,325}, {325,325}, {375,325}, {525,325}, {575,325}, {675,325}, {725,325}, {775,325},
                            {125,475}, {175,475}, {225,475}, {325,475}, {375,475}, {525,475}, {575,475}, {675,475}, {725,475}, {775,475},
                            {375,525}, {525,525}, {125,575}, {775,575}, {375,625}, {525,625},
                            {125,675}, {175,675}, {225,675}, {325,675}, {375,675}, {525,675}, {575,675}, {675,675}, {725,675}, {775,675},
                        };

                        std::vector<sf::Vector2f> brickCoords = {
                            {275,125}, {625,125},
                            {125,175}, {775,175},
                            {225,225}, {275,225}, {375,225}, {525,225}, {625,225}, {675,225},
                            {125,275}, {775,275},
                            {275,325}, {625,325},
                            
                            {275,475}, {625,475},
                            {125,525}, {775,525},
                            {225,575}, {275,575}, {375,575}, {525,575}, {625,575}, {675,575},
                            {125,625}, {775,625},
                            {275,675}, {625,675},
                        };

                        std::vector<sf::Vector2f> boxCoords = {
                            {175,175}, {225,175}, {275,175}, {325, 175}, {575,175}, {625,175}, {675,175}, {725,175},
                            {175,225}, {325,225}, {575,225}, {725,225},
                            {175,275}, {225,275}, {275,275}, {325, 275}, {575,275}, {625,275}, {675,275}, {725,275},
                            {175,525}, {225,525}, {275,525}, {325, 525}, {575,525}, {625,525}, {675,525}, {725,525},
                            {175,575}, {325,575}, {575,575}, {725,575},
                            {175,625}, {225,625}, {275,625}, {325, 625}, {575,625}, {625,625}, {675,625}, {725,625},
                        };

                        tanksInGame = 12;
                        wallsInGame = wallCoords.size();
                        bricksInGame = brickCoords.size();
                        boxesInGame = boxCoords.size();

                        for (const auto& coords : wallCoords) {
                            walls.push_back(Wall(coords, &wallTexture));
                        }

                        for (const auto& coords : brickCoords) {
                            bricks.push_back(Brick(coords, &brickTexture));
                        }

                        for (const auto& coords : boxCoords) {
                            boxes.push_back(Box(coords, &boxTexture));
                        }

                        for (int i = 0; i < tanksInGame; i++) {
                            enemyTanks.push_back(Tank(getRandomCordsForEnemySpawn(), 1.0f * gameSpeed, 0));
                            enemyBullets.push_back(Bullet());
                        }
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

                if (mousePosition.x > oneButton.getGlobalBounds().left && mousePosition.x < oneButton.getGlobalBounds().left + oneButton.getGlobalBounds().width
                    && mousePosition.y > oneButton.getGlobalBounds().top && mousePosition.y < oneButton.getGlobalBounds().top + oneButton.getGlobalBounds().height) {
                    mapOption = 1;
                }

                if (mousePosition.x > twoButton.getGlobalBounds().left && mousePosition.x < twoButton.getGlobalBounds().left + twoButton.getGlobalBounds().width
                    && mousePosition.y > twoButton.getGlobalBounds().top && mousePosition.y < twoButton.getGlobalBounds().top + twoButton.getGlobalBounds().height) {
                    mapOption = 2;
                }

                if (mousePosition.x > threeButton.getGlobalBounds().left && mousePosition.x < threeButton.getGlobalBounds().left + threeButton.getGlobalBounds().width
                    && mousePosition.y > threeButton.getGlobalBounds().top && mousePosition.y < threeButton.getGlobalBounds().top + threeButton.getGlobalBounds().height) {
                    mapOption = 3;
                }

                if (mousePosition.x > fourButton.getGlobalBounds().left && mousePosition.x < fourButton.getGlobalBounds().left + fourButton.getGlobalBounds().width
                    && mousePosition.y > fourButton.getGlobalBounds().top && mousePosition.y < fourButton.getGlobalBounds().top + fourButton.getGlobalBounds().height) {
                    mapOption = 4;
                }

                if (mousePosition.x > fiveButton.getGlobalBounds().left && mousePosition.x < fiveButton.getGlobalBounds().left + fiveButton.getGlobalBounds().width
                    && mousePosition.y > fiveButton.getGlobalBounds().top && mousePosition.y < fiveButton.getGlobalBounds().top + fiveButton.getGlobalBounds().height) {
                    mapOption = 0;
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

                for (int j = 0; j < bonusEvents.size(); j++) {
                    bonusEvents[j].getDestroyed(enemyBullets[i]);
                    bonusEvents[j].getDestroyed(playerBullet);
                }
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

            drawText(window, "Map: ", sf::Vector2f(400, 240));
            window.draw(oneButton);
            window.draw(twoButton);
            window.draw(threeButton);
            window.draw(fourButton);
            window.draw(fiveButton);

            if (mapOption == 0) {
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

                drawText(window, "Avaliable place: ", sf::Vector2f(260, 480), 120 - wallsInGame - bricksInGame - boxesInGame);

                if (wallsInGame + bricksInGame + boxesInGame > 119) {
                    disableInGameValues = true;
                }
                else {
                    disableInGameValues = false;
                }
            }
            else if (mapOption == 1) {
                drawText(window, "Map #1 - easy", sf::Vector2f(240, 300));
                drawText(window, "Enemy tanks: 3", sf::Vector2f(240, 360));
                drawText(window, "Walls: 32", sf::Vector2f(240, 400));
                drawText(window, "Bricks: 16", sf::Vector2f(240, 440));
                drawText(window, "Boxes: 16", sf::Vector2f(240, 480));

                window.draw(mapIcon1);
            }
            else if (mapOption == 2) {
                drawText(window, "Map #2 - normal", sf::Vector2f(240, 300));
                drawText(window, "Enemy tanks: 5", sf::Vector2f(240, 360));
                drawText(window, "Walls: 40", sf::Vector2f(240, 400));
                drawText(window, "Bricks: 16", sf::Vector2f(240, 440));
                drawText(window, "Boxes: 36", sf::Vector2f(240, 480));

                window.draw(mapIcon2);
            }
            else if (mapOption == 3) {
                drawText(window, "Map #3 - hard", sf::Vector2f(240, 300));
                drawText(window, "Enemy tanks: 8", sf::Vector2f(240, 360));
                drawText(window, "Walls: 40", sf::Vector2f(240, 400));
                drawText(window, "Bricks: 16", sf::Vector2f(240, 440));
                drawText(window, "Boxes: 24", sf::Vector2f(240, 480));

                window.draw(mapIcon3);
            }
            else if (mapOption == 4) {
                drawText(window, "Map #4 - very hard", sf::Vector2f(240, 300));
                drawText(window, "Enemy tanks: 12", sf::Vector2f(240, 360));
                drawText(window, "Walls: 52", sf::Vector2f(240, 400));
                drawText(window, "Bricks: 28", sf::Vector2f(240, 440));
                drawText(window, "Boxes: 40", sf::Vector2f(240, 480));

                window.draw(mapIcon4);
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

    mapIcon1Texture.loadFromFile("mapIcon1.png");
    mapIcon2Texture.loadFromFile("mapIcon2.png");
    mapIcon3Texture.loadFromFile("mapIcon3.png");
    mapIcon4Texture.loadFromFile("mapIcon4.png");


    one.loadFromFile("1.png");
    two.loadFromFile("2.png");
    three.loadFromFile("3.png");
    four.loadFromFile("4.png");
    five.loadFromFile("5.png");

    oneButton.setTexture(&one);
    oneButton.setSize(sf::Vector2f(25, 25));
    oneButton.setPosition(460, 240);

    twoButton.setTexture(&two);
    twoButton.setSize(sf::Vector2f(25, 25));
    twoButton.setPosition(500, 240);

    threeButton.setTexture(&three);
    threeButton.setSize(sf::Vector2f(25, 25));
    threeButton.setPosition(540, 240);

    fourButton.setTexture(&four);
    fourButton.setSize(sf::Vector2f(25, 25));
    fourButton.setPosition(580, 240);

    fiveButton.setTexture(&five);
    fiveButton.setSize(sf::Vector2f(25, 25));
    fiveButton.setPosition(620, 240);



    mapIcon1.setTexture(&mapIcon1Texture);
    mapIcon1.setSize(sf::Vector2f(200, 180));
    mapIcon1.setPosition(430, 300);

    mapIcon2.setTexture(&mapIcon2Texture);
    mapIcon2.setSize(sf::Vector2f(200, 180));
    mapIcon2.setPosition(430, 300);

    mapIcon3.setTexture(&mapIcon3Texture);
    mapIcon3.setSize(sf::Vector2f(200, 180));
    mapIcon3.setPosition(430, 300);

    mapIcon4.setTexture(&mapIcon4Texture);
    mapIcon4.setSize(sf::Vector2f(200, 180));
    mapIcon4.setPosition(430, 300);



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