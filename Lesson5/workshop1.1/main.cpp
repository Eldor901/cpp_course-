#include <SFML/Graphics.hpp>
#include <cmath>

void initCursor(sf::ConvexShape &shape)
{
    shape.setPosition({100, 150});

    shape.setPointCount(7);
    shape.setPoint(0, {0, 0});
    shape.setPoint(1, {60, 0});
    shape.setPoint(2, {60, 40});
    shape.setPoint(3, {120, -25});
    shape.setPoint(4, {60, -90});
    shape.setPoint(5, {60, -50});
    shape.setPoint(6, {0, -50});
    shape.setFillColor(sf::Color(0xFF, 0xFF, 0));
    shape.setOutlineColor(sf::Color(0, 0, 0));
    shape.setOutlineThickness(3);
    shape.setRotation(-85);
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &shape)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(shape);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Hello it is mee cursor", sf::Style::Default, settings);

    sf::ConvexShape shape;

    initCursor(shape);
    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, shape);
    }
}