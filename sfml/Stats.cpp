#include "Stats.h"
//#include "Tank.h"


Stats::Stats() {
   this->hp = 0;
   this->kills = 0;
   this->dmgBullet = 100;
   //this->gameClock = 0;
};


void Stats::displayStats(sf::RenderWindow& window) {
    sf::Font font;
    sf::Text text;
    font.loadFromFile("roboto.ttf");
    text.setFont(font);
    text.setCharacterSize(15);
    text.setFillColor(sf::Color::Black);

    text.setString("Kills: " + kills);

    text.setPosition(950, 200); // Ustaw pozycjê tekstu na ekranie

    window.draw(text);
}

void Stats::addKill() {
    kills++;
}

