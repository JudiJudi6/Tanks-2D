#ifndef STATSWINDOW_H
#define STATSWINDOW_H
#pragma once
#include <SFML/Graphics.hpp>

extern int destroyedTanks; // zniszczone czo³gi
extern int gameTime; // czas gry
extern bool countTime; // flaga kontroluj¹ca odliczanie zegara
extern sf::Clock gameTimeClock; // zegar

void addKill(); 
void drawText(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, int number = -1);
void drawTextFloat(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, float number = -1);
void startGameTime();
void countGameTime();
void stopGameTime();


#undef STATSWINDOW_H
#endif // STATSWINDOW_H