#pragma once

#include <SFML/Graphics.hpp>
struct Ball
{
    sf::CircleShape shape;
    sf::Font font;
    sf::Text text;
    float speed = 0;
    float speedy = 250;
};
void Init(Ball &ball);
void updateBallElements(Ball &ball, float &dt);
