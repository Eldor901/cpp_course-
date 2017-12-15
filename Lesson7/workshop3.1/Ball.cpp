#include "Ball.h"
void Init(Ball &ball)
{
    ball.shape.setRadius(120);
    ball.shape.setFillColor(sf::Color(255, 255, 0));
    ball.shape.setPosition({400, 400});
    ball.shape.setOutlineThickness(5);
    ball.shape.setOutlineColor(sf::Color(0, 0, 205));
    ball.font.loadFromFile("text.ttf");
    ball.text.setFont(ball.font);
    ball.text.setString("ELDOR");
    ball.text.setCharacterSize(50);
    ball.text.setFillColor(sf::Color(0, 0, 0));
    ball.text.setPosition({300, 350});
    ball.text.setOrigin({60, 30});
    ball.shape.setOrigin({100, 100});
}
void updateBallElements(Ball &ball, float &dt)
{
    sf::Vector2f position = ball.shape.getPosition();
    ball.speed += ball.speedy * dt;
    position.y += ball.speed * dt;
    if ((position.y + ball.shape.getRadius() + ball.shape.getOutlineThickness() >= 600) && (ball.speed > 0))
    {
        ball.speed = -ball.speed;
    }
    ball.shape.setPosition(position);
    ball.text.setPosition(position);
}