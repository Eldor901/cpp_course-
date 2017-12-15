#include <iostream>
#include <cmath>
#include "Axis.h"

float distance(sf::Vector2f &mousePosition)
{
    sf::Vector2f farDistance = mousePosition - CENTER;
    return std::sqrt(std::pow(farDistance.x, 2) + std::pow(farDistance.y, 2));
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
    std::cout << "distance between mouse cursor and center is  " << distance(mousePosition) << std::endl;
}

void pollEvent(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}
void redrawFrame(sf::RenderWindow &window, sf::VertexArray &axis, sf::RectangleShape &square)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(axis);
    window.draw(square);
    window.display();
}
void createWindow(sf::RenderWindow &window)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "axis", sf::Style::Default, settings);
}
int main()
{
    sf::RenderWindow window;
    createWindow(window);
    sf::VertexArray axis(sf::Lines, 2);
    sf::RectangleShape square;
    sf::Vector2f mousePosition = CENTER;
    init(axis, square);
    while (window.isOpen())
    {
        pollEvent(window, mousePosition);
        updateAxis(axis, mousePosition);
        redrawFrame(window, axis, square);
    }
    return 0;
}