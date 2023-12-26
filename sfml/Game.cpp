#include "Game.h"
#include <iostream>
#include "Global.h"

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
    sf::RenderWindow window(sf::VideoMode(1100, 800), "Tanks 2D", sf::Style::Close); //okno 
    window.setMouseCursorVisible(true); //ustawienie kursora
    Tank playerTank(sf::Vector2f(450, 400), 1.6f * gameSpeed, 1); //obiekt player tank
    Bullet playerBullet; //obiekt player bullet

    window.setFramerateLimit(30);

    sf::Clock clock;
    sf::Time elapsed;
    unsigned int frameCount = 0;

    std::srand(std::time(0));
    sf::Clock frameClock;
    clock.restart();

    while (window.isOpen()) {
        sf::Event evnt;
        while (window.pollEvent(evnt)) { //nas³uchiwanie na zamkniêcie okna
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            }
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window); //œledzenie pozycji myszy

        if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left) { //obs³uga przycisków
            if (!mouseClicked) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (mousePosition.x > battleButton.getGlobalBounds().left && mousePosition.x < battleButton.getGlobalBounds().left + battleButton.getGlobalBounds().width
                    && mousePosition.y > battleButton.getGlobalBounds().top && mousePosition.y < battleButton.getGlobalBounds().top + battleButton.getGlobalBounds().height) {
                    drawText(window, "Loading...", sf::Vector2f(520, 540));
                    window.display();
                    
                    if (mapOption == 0) { 
                        std::vector<int> cordXarr = { 125, 175, 225, 275, 325, 375, 525, 575, 625, 675, 725, 775 }; //dostêpne koordynaty
                        std::vector<int> cordYarr = { 125, 175, 225, 275, 325, 475, 525, 575, 625, 675 }; //dostêpne koordynaty

                        for (int i = 0; i < cordXarr.size(); i++) {
                            for (int j = 0; j < cordYarr.size(); j++) {
                                Global::getInstance().availablePlace.push_back(sf::Vector2f(cordXarr[i], cordYarr[j]));
                            }
                        }
                        for (int i = 0; i < tanksInGame; i++) { //generowanie przeciwników
                            Global::getInstance().enemyTanks.push_back(Tank(Global::getInstance().getRandomCordsForEnemySpawn(), 1.0f * gameSpeed, 0));
                            Global::getInstance().enemyBullets.push_back(Bullet());
                        }

                        for (int i = 0; i < wallsInGame; i++) { //generowanie œcian
                            Global::getInstance().walls.push_back(Wall(Global::getInstance().getRandomCordsForWalls(), &Global::getInstance().wallTexture));
                        }

                        for (int i = 0; i < bricksInGame; i++) { //generowanie murów
                            Global::getInstance().bricks.push_back(Brick(Global::getInstance().getRandomCordsForWalls(), &Global::getInstance().brickTexture));
                        }

                        for (int i = 0; i < boxesInGame; i++) { //generowanie skrzyñ
                            Global::getInstance().boxes.push_back(Box(Global::getInstance().getRandomCordsForWalls(), &Global::getInstance().boxTexture));
                        }
                    }
                    else if (mapOption == 1) {
                        std::vector<sf::Vector2f> wallCoords = { //koordynaty œcian
                            {125,125}, {175,125}, {225,125}, {275,125}, {625,125}, {675,125}, {725,125}, {775,125},
                            {125,175}, {775,175}, {125,225}, {775,225}, {125,275}, {275, 275}, {625,275}, {775,275},
                            {125,525}, {275,525}, {625,525}, {775,525}, {125,575}, {775,575},  {125,625}, {775,625},
                            {125,675}, {175,675}, {225,675}, {275,675}, {625,675}, {675,675}, {725,675}, {775,675}
                        };

                        std::vector<sf::Vector2f> brickCoords = { //koorrdynaty murów
                            {275,175}, {625,175}, {275,225}, {625,225}, {175,275}, {225,275}, {675,275}, {725,275},
                            {175,525}, {225,525}, {675,525}, {725,525}, {275,575}, {625,575}, {275,625}, {625,625}
                        };

                        std::vector<sf::Vector2f> boxCoords = { //koordynaty skrzyñ
                            {175,175}, {225,175}, {175,225}, {225,225}, {675,175}, {725,175}, {675,225}, {725,225},
                            {175,575}, {225,575}, {175,625}, {225,625}, {675,575}, {725,575}, {675, 625}, {725,625}
                        };
                         
                        tanksInGame = 3; //liczba czo³gów
                        wallsInGame = wallCoords.size();
                        bricksInGame = brickCoords.size();
                        boxesInGame = boxCoords.size();

                        for (const auto& coords : wallCoords) { //generowanie œcian
                            Global::getInstance().walls.push_back(Wall(coords, &Global::getInstance().wallTexture));
                        }

                        for (const auto& coords : brickCoords) { //generowanie murów
                            Global::getInstance().bricks.push_back(Brick(coords, &Global::getInstance().brickTexture));
                        }

                        for (const auto& coords : boxCoords) { //generowanie skrzyñ
                            Global::getInstance().boxes.push_back(Box(coords, &Global::getInstance().boxTexture));
                        }

                        for (int i = 0; i < tanksInGame; i++) { //generowanie przeciwników
                            Global::getInstance().enemyTanks.push_back(Tank(Global::getInstance().getRandomCordsForEnemySpawn(), 1.0f * gameSpeed, 0));
                            Global::getInstance().enemyBullets.push_back(Bullet());
                        }
                    }
                    else if (mapOption == 2) { 
                        std::vector<sf::Vector2f> wallCoords = { //koordynaty œcian
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

                        std::vector<sf::Vector2f> brickCoords = { //koordynaty murów
                            {325,175}, {575,175},
                            {275,225}, {625,225},
                            {225,275}, {675,275},
                            {175,325}, {725,325},

                            {175,475}, {725,475},
                            {225,525}, {675,525},
                            {275,575}, {625,575},
                            {325,625}, {575,625},
                        };

                        std::vector<sf::Vector2f> boxCoords = { //koordynaty skrzyñ
                            {175,175}, {225,175}, {275,175}, {625,175}, {675,175}, {725,175},
                            {175,225}, {225,225}, {675,225}, {725,225},
                            {175,275}, {375,275}, {525,275}, {725,275},
                            {325,325}, {375,325}, {525,325}, {575,325},

                            {325,475}, {375,475}, {525,475}, {575,475},
                            {175,525}, {375,525}, {525,525}, {725,525},
                            {175,575}, {225,575}, {675,575}, {725,575},
                            {175,625}, {225,625}, {275,625}, {625,625}, {675,625}, {725,625},
                        };

                        tanksInGame = 5; //liczba przeciwników
                        wallsInGame = wallCoords.size();
                        bricksInGame = brickCoords.size();
                        boxesInGame = boxCoords.size();

                        for (const auto& coords : wallCoords) { //generowanie œcian
                            Global::getInstance().walls.push_back(Wall(coords, &Global::getInstance().wallTexture));
                        }

                        for (const auto& coords : brickCoords) { //generowanie murów
                            Global::getInstance().bricks.push_back(Brick(coords, &Global::getInstance().brickTexture));
                        }

                        for (const auto& coords : boxCoords) { //generowanie skrzyñ
                            Global::getInstance().boxes.push_back(Box(coords, &Global::getInstance().boxTexture));
                        }

                        for (int i = 0; i < tanksInGame; i++) { //generowanie przeciwników
                            Global::getInstance().enemyTanks.push_back(Tank(Global::getInstance().getRandomCordsForEnemySpawn(), 1.0f * gameSpeed, 0));
                            Global::getInstance().enemyBullets.push_back(Bullet());
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
                            Global::getInstance().walls.push_back(Wall(coords, &Global::getInstance().wallTexture));
                        }

                        for (const auto& coords : brickCoords) {
                            Global::getInstance().bricks.push_back(Brick(coords, &Global::getInstance().brickTexture));
                        }

                        for (const auto& coords : boxCoords) {
                            Global::getInstance().boxes.push_back(Box(coords, &Global::getInstance().boxTexture));
                        }

                        for (int i = 0; i < tanksInGame; i++) {
                            Global::getInstance().enemyTanks.push_back(Tank(Global::getInstance().getRandomCordsForEnemySpawn(), 1.0f * gameSpeed, 0));
                            Global::getInstance().enemyBullets.push_back(Bullet());
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
                            Global::getInstance().walls.push_back(Wall(coords, &Global::getInstance().wallTexture));
                        }

                        for (const auto& coords : brickCoords) {
                            Global::getInstance().bricks.push_back(Brick(coords, &Global::getInstance().brickTexture));
                        }

                        for (const auto& coords : boxCoords) {
                            Global::getInstance().boxes.push_back(Box(coords, &Global::getInstance().boxTexture));
                        }

                        for (int i = 0; i < tanksInGame; i++) {
                            Global::getInstance().enemyTanks.push_back(Tank(Global::getInstance().getRandomCordsForEnemySpawn(), 1.0f * gameSpeed, 0));
                            Global::getInstance().enemyBullets.push_back(Bullet());
                        }
                    }

                    startGame = true;
                    playerTank.startGameTime();
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
                    playerTank.destroyedTanks = 0;

                    tanksInGame = 3;
                    Global::getInstance().clearVectors();
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            playerTank.moveTop();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            playerTank.moveLeft();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            playerTank.moveBottom();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            playerTank.moveRight();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            playerBullet.shot(playerTank.getBulletDirection(), playerTank.body.getPosition().x, playerTank.body.getPosition().y, playerTank.getDamage());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
            if (!qKeyPressed) {
                if (playerTank.getMines() > 0) {
                    Global::getInstance().minesOnMap.push_back(Mine(playerTank.body.getPosition()));
                    playerTank.useOneMine();
                }
                qKeyPressed = true;
            }
        }
        else {
            qKeyPressed = false;
        }

        playerTank.countGameTime();
        window.clear();
        window.draw(map);

        if (startGame) {
            for (int i = 0; i < Global::getInstance().minesOnMap.size(); i++) {
                window.draw(Global::getInstance().minesOnMap[i].body);
            }

            playerBullet.drawBullet(window);
            window.draw(playerTank.body);
            playerTank.eventBonusIntersects();

            for (int i = 0; i < tanksInGame; i++) {
                Global::getInstance().enemyTanks[i].getHitted(playerBullet);
                Global::getInstance().enemyTanks[i].getHittedAnimation();
                playerTank.getHitted(Global::getInstance().enemyBullets[i]);
                Global::getInstance().enemyBullets[i].drawBullet(window);
                Global::getInstance().enemyBullets[i].updateBullet();
                Global::getInstance().enemyTanks[i].drawTank(window);
                Global::getInstance().enemyTanks[i].enemyIntelligence(playerTank, Global::getInstance().enemyBullets[i], clock);
                Global::getInstance().enemyTanks[i].respawnEnemy();
                Global::getInstance().enemyTanks[i].eventBonusIntersects();
                Global::getInstance().enemyTanks[i].mineIntersects();

                for (int j = 0; j < Global::getInstance().bonusEvents.size(); j++) {
                    Global::getInstance().bonusEvents[j].getDestroyed(Global::getInstance().enemyBullets[i]);
                    Global::getInstance().bonusEvents[j].getDestroyed(playerBullet);
                }
            }

            for (int i = 0; i < bricksInGame; i++) {
                window.draw(Global::getInstance().bricks[i].body);
                for (int j = 0; j < Global::getInstance().enemyBullets.size(); j++) {
                    Global::getInstance().bricks[i].GetHitted(Global::getInstance().enemyBullets[j]);
                }
                Global::getInstance().bricks[i].GetHitted(playerBullet);
            }

            for (int i = 0; i < boxesInGame; i++) {
                window.draw(Global::getInstance().boxes[i].body);
                for (int j = 0; j < Global::getInstance().enemyBullets.size(); j++) {
                    Global::getInstance().boxes[i].GetHitted(Global::getInstance().enemyBullets[j]);
                }
                Global::getInstance().boxes[i].GetHitted(playerBullet);
            }

            for (int i = 0; i < wallsInGame; i++) {
                window.draw(Global::getInstance().walls[i].body);
                for (int j = 0; j < Global::getInstance().enemyBullets.size(); j++) {
                    Global::getInstance().walls[i].GetHitted(Global::getInstance().enemyBullets[j]);
                }
                Global::getInstance().walls[i].GetHitted(playerBullet);
            }

            for (int i = 0; i < Global::getInstance().bonusEvents.size(); i++) {
                Global::getInstance().bonusEvents[i].drawEvent(window);
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
            playerTank.stopGameTime();
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

            int minutes = playerTank.gameTime / 60;
            int seconds = playerTank.gameTime % 60;

            drawText(window, "Game over", sf::Vector2f(400, 300));
            drawText(window, "Points: ", sf::Vector2f(350, 340), playerTank.gameTime + ((playerTank.destroyedTanks - 1) * 15));
            drawText(window, "Game time: ", sf::Vector2f(350, 380), minutes);
            if (seconds < 10) {
                drawText(window, ": 0", sf::Vector2f(470, 380), seconds);
            }
            else {
                drawText(window, ": ", sf::Vector2f(470, 380), seconds);
            }
            drawText(window, "Destroyed enemies: ", sf::Vector2f(350, 420), playerTank.destroyedTanks - 1);

            drawText(window, "Tanks 2D", sf::Vector2f(240, 240));
        }

        playerBullet.updateBullet();
        playerTank.getHittedAnimation();
        window.draw(panel);
        drawText(window, "Kills: ", sf::Vector2f(950, 200), playerTank.destroyedTanks);
        drawText(window, "Game time: ", sf::Vector2f(950, 300), playerTank.gameTime);
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
        // Pomiar czasu miêdzy klatkami
        elapsed = frameClock.restart();

        // Zliczanie klatek
        frameCount++;

        // Wyœwietlanie liczby klatek co sekundê
        if (elapsed.asSeconds() <= 1) {
            float fps = static_cast<float>(frameCount) / elapsed.asSeconds();
            std::cout << "FPS: " << fps << std::endl;

            // Zerowanie licznika klatek
            frameCount = 0;
        }
    }
}

void Game::loadTextures() {
    Global::getInstance().loadTextures();
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



void Game::drawText(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, int number) {
    sf::Font font;
    font.loadFromFile("roboto.ttf");
    std::string fullText;
    sf::Text displayText;
    displayText.setFont(font);
    displayText.setCharacterSize(20);
    displayText.setFillColor(sf::Color::White);

    if (number == -1) {
        fullText = text;
    }
    else {
        fullText = text + std::to_string(number);
    }
    displayText.setString(fullText);
    displayText.setPosition(position);

    window.draw(displayText);
}

void Game::drawTextFloat(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, float number) {
    sf::Font font;
    font.loadFromFile("roboto.ttf");
    std::string fullText;
    sf::Text displayText;
    displayText.setFont(font);
    displayText.setCharacterSize(20);
    displayText.setFillColor(sf::Color::White);

    if (number == -1) {
        fullText = text;
    }
    else {
        fullText = text + std::to_string(std::round(number * 10) / 10);
    }
    displayText.setString(fullText);
    displayText.setPosition(position);

    window.draw(displayText);
}