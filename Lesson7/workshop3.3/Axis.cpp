#include "Axis.h"

void init(sf::VertexArray &axis, sf::RectangleShape &square)
{
    axis[0].position = CENTER;
    axis[0].color = sf::Color(0, 0, 0);
    axis[1].color = sf::Color(0, 0, 0);
    square.setSize({16, 16});
    square.setOrigin({8, 8});
    square.setPosition(CENTER);
    square.setFillColor(sf::Color(0, 0, 0));
}
void updateAxis(sf::VertexArray &axis, sf::Vector2f &mousePosition)
{
    axis[1].position = mousePosition;
}