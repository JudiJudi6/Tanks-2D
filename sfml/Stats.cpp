#include "Stats.h"


Stats::Stats() {};

void Stats::displayStats(sf::RenderWindow& window) const {
    sf::Font font;
    font.loadFromFile("arial.ttf"); // Za�aduj czcionk�

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    text.setString("Kills: " + std::to_string(kills) +
        "\nGame Time: " + std::to_string(gameTime) + " seconds" +
        "\nHP: " + std::to_string(hp) +
        "\nDamage Bullet: " + std::to_string(dmgBullet));

    text.setPosition(10, 10); // Ustaw pozycj� tekstu na ekranie

    window.draw(text);
}