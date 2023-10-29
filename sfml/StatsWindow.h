#ifndef STATSWINDOW_H
#define STATSWINDOW_H
#pragma once
#include <SFML/Graphics.hpp>

extern int destroyedTanks;
extern int gameTime;
extern bool countTime;
extern sf::Clock gameTimeClock;

void addKill();
void drawText(sf::RenderWindow& window, const std::string& text, const sf::Vector2f& position, int number = -1);
void startGameTime();
void countGameTime();
void stopGameTime();


#undef STATSWINDOW_H
#endif // STATSWINDOW_H