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

    bool mouseClicked = false; //flaga sterowana klikniêciem myszy
    bool disableInGameValues = false; // flaga kontrolujaca ilosc blokow na mapie
    bool startGame = false; //flaga zmieniajaca ekran
    bool displayEndScreen = false; //flaga zmieniajaca ekran
    bool qKeyPressed = false; //flaga kontrolujaca wcisniecie "Q"

    int mapOption = 0; //wybor mapy 0-4

	float gameSpeed; //predkosc gry
	int tanksInGame; //liczba przeciwnikow
	int boxesInGame; //liczba skrzyn na mapie
	int bricksInGame; //liczba murow na mapie
	int wallsInGame; // liczba scian na mapie

public:
    Game(); //konstruktor gry
    void gameStart(); //metoda obslugujaca grê
    void loadTextures(); //wczytywanie tekstur
};

