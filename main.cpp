#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>
constexpr unsigned WIDTH = 800;
constexpr unsigned HEIGT = 600;
int main()
{
    constexpr int pointCount = 200;
    const sf::Vector2f ellipseRadius = {400.f, 300.f};
    const float period = 4.f;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WIDTH, HEIGT}), "Ellipse",
        sf::Style::Default, settings);
    sf::Clock clock;

    sf::ConvexShape ellipse;
    ellipse.setPosition({400, 320});
    ellipse.setFillColor(sf::Color(135, 38, 87)); // color raspberry

    ellipse.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float add = 200 * sin(6 * angle);
        sf::Vector2f point = {
            add * std::sin(angle),
            add * std::cos(angle)};
        ellipse.setPoint(pointNo, point);
    }
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        const float dt = clock.getElapsedTime().asSeconds();
        float phase = dt * float(2 * M_PI * 200) / float(pointCount);
        float x = 100 * std::sin(phase / period);
        float y = 100 * std::cos(phase / period);
        sf::Vector2f offset = {x, y};
        ellipse.setPosition(ellipseRadius + offset);

        window.clear();
        window.draw(ellipse);
        window.display();
    }
}