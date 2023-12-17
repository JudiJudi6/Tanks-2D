#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Bullet.h"
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
    sf::Texture one;
    sf::Texture two;
    sf::Texture three;
    sf::Texture four;
    sf::Texture five;
    
    sf::Texture mapIcon1Texture;
    sf::Texture mapIcon2Texture;
    sf::Texture mapIcon3Texture;
    sf::Texture mapIcon4Texture;


    sf::RectangleShape map;
    sf::RectangleShape panel;
    sf::RectangleShape welcomeScreen;
    sf::RectangleShape battleButton;
    sf::RectangleShape restartButton;

    sf::RectangleShape oneButton;
    sf::RectangleShape twoButton;
    sf::RectangleShape threeButton;
    sf::RectangleShape fourButton;
    sf::RectangleShape fiveButton;

    sf::RectangleShape mapIcon1;
    sf::RectangleShape mapIcon2;
    sf::RectangleShape mapIcon3;
    sf::RectangleShape mapIcon4;


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

    int mapOption = 0;

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

