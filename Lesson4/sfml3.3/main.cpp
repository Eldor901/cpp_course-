#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Eye
{
    sf::ConvexShape big;
    sf::ConvexShape small;

    sf::Vector2f position;

    float rotation = 0;
};

sf::Vector2f toEuclidian(float radiusX, float radiusY, float angle)
{
    return {
        radiusX * float(cos(angle)),
        radiusY * float(sin(angle))};
}

void updateEye1Elements(Eye &eye1)
{
    constexpr float rotationRadiusX = 40.f;
    constexpr float rotationRadiusY = 80.f;

    const sf::Vector2f big1Offset = toEuclidian(rotationRadiusX, rotationRadiusY, eye1.rotation);
    eye1.small.setPosition(eye1.position + big1Offset);
}

void updateEye2Elements(Eye &eye2)
{
    constexpr float rotationRadiusX = 40.f;
    constexpr float rotationRadiusY = 80.f;
    const sf::Vector2f big2Offset = toEuclidian(rotationRadiusX, rotationRadiusY, eye2.rotation);
    eye2.small.setPosition(eye2.position + big2Offset);
}
void initEyes(Eye &eye1, Eye &eye2)
{
    const sf::Vector2f bigRadius = {70.f, 140.f};
    const sf::Vector2f smallRadius = {30.f, 40.f};
    constexpr int pointCount = 200;

    eye1.position = {280, 300};
    eye2.position = {520, 300};

    eye1.big.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eye1.big.setPointCount(pointCount);
    eye1.big.setPosition(eye1.position);
    eye2.big.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eye2.big.setPointCount(pointCount);
    eye2.big.setPosition(eye2.position);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            bigRadius.x * std::sin(angle),
            bigRadius.y * std::cos(angle)};
        eye1.big.setPoint(pointNo, point);
        eye2.big.setPoint(pointNo, point);
    }

    eye1.small.setPointCount(pointCount);
    eye1.small.setFillColor(sf::Color(0x00, 0x00, 0x00));
    eye2.small.setPointCount(pointCount);
    eye2.small.setFillColor(sf::Color(0x00, 0x00, 0x00));
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            smallRadius.x * std::sin(angle),
            smallRadius.y * std::cos(angle)};
        eye1.small.setPoint(pointNo, point);
        eye2.small.setPoint(pointNo, point);
    }

    updateEye1Elements(eye1);
    updateEye2Elements(eye2);
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

void updateEyes(const sf::Vector2f &mousePosition, Eye &eye1, Eye &eye2)
{
    const sf::Vector2f rotationRadius = {40.f, 80.f};

    float p1 = std::pow((mousePosition.x - eye1.position.x), 2) + std::pow((mousePosition.y - eye1.position.y), 2);
    float p2 = std::pow((mousePosition.x - eye2.position.x), 2) + std::pow((mousePosition.y - eye2.position.y), 2);

    sf::Vector2f d1 = mousePosition - eye1.position;
    sf::Vector2f d2 = mousePosition - eye2.position;

    float angle1 = atan2(d1.y, d1.x);
    float angle2 = atan2(d2.y, d2.x);

    float R = std::pow(rotationRadius.x * std::cos(angle1), 2) + std::pow(rotationRadius.y * std::sin(angle1), 2);
    float L = std::pow(rotationRadius.x * std::cos(angle2), 2) + std::pow(rotationRadius.y * std::sin(angle2), 2);
    if (p1 > R)
    {
        const sf::Vector2f firstEyeDelta = mousePosition - eye1.position;
        eye1.rotation = atan2(firstEyeDelta.y, firstEyeDelta.x);

        updateEye1Elements(eye1);
    }
    else
    {
        eye1.small.setPosition(mousePosition);
    }
    if (p2 > L)
    {
        const sf::Vector2f secondEyeDelta = mousePosition - eye2.position;
        eye2.rotation = atan2(secondEyeDelta.y, secondEyeDelta.x);

        updateEye2Elements(eye2);
    }
    else
    {
        eye2.small.setPosition(mousePosition);
    }
}

void redrawFrame(sf::RenderWindow &window, Eye &eye1, Eye &eye2)
{
    window.clear();
    window.draw(eye1.big);
    window.draw(eye1.small);
    window.draw(eye2.big);
    window.draw(eye2.small);
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
        "Eyes follows mouse", sf::Style::Default, settings);

    Eye eye1;
    Eye eye2;
    sf::Vector2f mousePosition;

    initEyes(eye1, eye2);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        updateEyes(mousePosition, eye1, eye2);
        redrawFrame(window, eye1, eye2);
    }
}