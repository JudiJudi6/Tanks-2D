#pragma once
#include <SFML/Graphics.hpp>
#include "Tank.h"
#include "Bullet.h"

#pragma once
class BonusEvent
{
private:
	int flag; // flaga okreœlaj¹ca typ bonusu: Damage, Speed, HP, Mine
public:
	BonusEvent(int flag, sf::Vector2f position); //Konstruktor przyjmuj¹cy flagê oraz pozycje obiektu
	void drawEvent(sf::RenderWindow& window); //Metoda rysuj¹ca obiekt w oknie
	void action(Tank &tank); //Metoda wywo³ywana podczas interakcji z czo³giem
	void getDestroyed(Bullet &bullet); //Metoda nas³uchuj¹ca na zniszczenie bonusu

	sf::RectangleShape body; 
};

