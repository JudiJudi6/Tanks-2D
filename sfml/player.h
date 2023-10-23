#include <SFML/Graphics.hpp>

class Player {
private:
    sf::RectangleShape body;
    sf::Texture textureUp;
    sf::Texture textureDown;
    sf::Texture textureLeft;
    sf::Texture textureRight;

public:
    Player(float x, float y);
    void move(float offsetX, float offsetY);
    sf::Vector2f getPosition() const;
    void draw(sf::RenderWindow& window);
    float left() const;
    float top() const;
    float right() const;
    float bottom() const;
};