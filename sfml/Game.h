#include <SFML/Graphics.hpp>
#include "globals.h"
#include "Tank.h"
#include "Bullet.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include "Wall.h"
#include "Brick.h"	
#include "Box.h"
#include "Mine.h"
#pragma once
class Game
{


    sf::Texture mapTexture;
    sf::Texture panelTexture;
    sf::Texture welcomeScreenTexture;
    sf::Texture battleButtonTexture;
    sf::Texture restartButtonTexture;
    sf::Texture addIconTexture;
    sf::Texture minusIconTexture;

    sf::RectangleShape map;
    sf::RectangleShape panel;
    sf::RectangleShape welcomeScreen;
    sf::RectangleShape battleButton;
    sf::RectangleShape restartButton;

    sf::RectangleShape tanksInGameIncrese;
    sf::RectangleShape tanksInGameDecrease;

    sf::RectangleShape boxesInGameIncrease;
    sf::RectangleShape boxesInGameDecrease;

    sf::RectangleShape bricksInGameIncrese;
    sf::RectangleShape bricksInGameDecrease;

    sf::RectangleShape wallsInGameIncrese;
    sf::RectangleShape wallsInGameDecrease;

    sf::RectangleShape gameSpeedIncrese;
    sf::RectangleShape gameSpeedDecrease;

    bool mouseClicked = false;
    bool renderElements = false;
    bool disableInGameValues = false;
    bool startGame = false;
    bool displayEndScreen = false;
    bool qKeyPressed = false;

	float gameSpeed;
	int tanksInGame;
	int boxesInGame;
	int bricksInGame;
	int wallsInGame;

public:
    Game();
    void gameStart();
    void loadTextures();
};

