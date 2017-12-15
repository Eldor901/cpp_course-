#include "Ball.h"

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned MAX_FPS = 60;

void createWindow(sf::RenderWindow &window)
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "Eldor", sf::Style::Default, settings);
    window.setFramerateLimit(MAX_FPS);
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
void redrawFrame(sf::RenderWindow &window, Ball &ball)
{
    window.clear(sf::Color(255, 255, 255));
    window.draw(ball.shape);
    window.draw(ball.text);
    window.display();
}

int main()
{

    sf::RenderWindow window;
    createWindow(window);

    sf::Clock clock;

    Ball ball;
    Init(ball);
    while (window.isOpen())
    {
        pollEvents(window);
        float dt = clock.restart().asSeconds();
        updateBallElements(ball, dt);
        redrawFrame(window, ball);
    }
}