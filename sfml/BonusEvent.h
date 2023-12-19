#include "Tank.h"
#include <SFML/Graphics.hpp>
#pragma once
class BonusEvent
{
private:
	int flag; // flaga okre�laj�ca typ bonusu: Damage, Speed, HP, Mine
public:
	BonusEvent(int flag, sf::Vector2f position); //Konstruktor przyjmuj�cy flag� oraz pozycje obiektu
	void drawEvent(sf::RenderWindow& window); //Metoda rysuj�ca obiekt w oknie
	void action(Tank &tank); //Metoda wywo�ywana podczas interakcji z czo�giem
	void getDestroyed(Bullet &bullet); //Metoda nas�uchuj�ca na zniszczenie bonusu

	sf::RectangleShape body; 
};

