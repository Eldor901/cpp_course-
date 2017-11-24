#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

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
    shape.setOrigin(60, -25);
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}
void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
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

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &shape, float &dt)
{
    const sf::Vector2f delta = mousePosition - shape.getPosition();
    float angle = atan2(delta.y, delta.x);
    if (angle < 0)
    {
        angle = angle + 2 * M_PI;
    }
    angle = toDegrees(angle);
    const float timeRotation = 90 * dt;
    const float mouseRotation = std::abs(angle - shape.getRotation());
    if (angle > shape.getRotation())
    {
        if ((angle - 180) < shape.getRotation())
        {
            shape.setRotation(shape.getRotation() + std::min(timeRotation, mouseRotation));
        }
        else
        {
            shape.setRotation(shape.getRotation() - std::min(timeRotation, mouseRotation));
        }
    }
    else
    {
        if ((angle + 180) > shape.getRotation())
        {
            shape.setRotation(shape.getRotation() - std::min(timeRotation, mouseRotation));
        }
        else
        {
            shape.setRotation(shape.getRotation() + std::min(timeRotation, mouseRotation));
        }
    }

    if ((delta.x != 0) && (delta.y != 0))
    {
        sf::Vector2f movement = {
            delta.x / std::sqrt(delta.x * delta.x + delta.y * delta.y),
            delta.y / std::sqrt(delta.x * delta.x + delta.y * delta.y)};
        sf::Vector2f speed = movement * 20.f * dt;
        shape.setPosition(shape.getPosition() + speed);
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
        "Hello it is me Cursor", sf::Style::Default, settings);
    sf::Clock clock;

    sf::ConvexShape shape;
    sf::Vector2f mousePosition;

    initCursor(shape);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        float dt = clock.restart().asSeconds();
        update(mousePosition, shape, dt);
        redrawFrame(window, shape);
    }
}