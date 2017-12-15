#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned BALL_SIZE = 40;
using namespace std;

struct Circle
{
    sf::CircleShape shapes;
    sf::Vector2f speed;
};

void init(std::vector<Circle> &circles)
{
    const vector<sf::Color> colors = {sf::Color(0, 255, 17),
                                      sf::Color(255, 255, 0),
                                      sf::Color(122, 122, 46),
                                      sf::Color(219, 33, 33),
                                      sf::Color(28, 44, 186)};

    const vector<sf::Vector2f> speeds = {
        {50.f, 20.f},
        {100.f, 150.f},
        {150.f, 200.f},
        {-100.f, 300.f},
        {100.f, -120.f}};

    const vector<sf::Vector2f> positions = {
        {100, 100},
        {200, 300},
        {400, 500},
        {50, 500},
        {600, 100}};
    for (size_t fi = 0; fi < circles.size(); ++fi)
    {
        circles[fi].shapes.setPosition(positions[fi]);
        circles[fi].shapes.setRadius(BALL_SIZE);
        circles[fi].shapes.setFillColor(colors[fi]);
        circles[fi].speed = speeds[fi];
    }
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event{};
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

void update(std::vector<Circle> &circles, float &dt)
{
    for (size_t fi = 0; fi < circles.size(); ++fi)
    {
        for (size_t si = fi + 1; si < circles.size(); ++si)
        {
            sf::Vector2f direction = circles[fi].shapes.getPosition() - circles[si].shapes.getPosition();
            float distance1 = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
            float distance2 = 2 * BALL_SIZE;
            if (distance1 <= distance2)
            {
                sf::Vector2f acceleration = circles[fi].speed - circles[si].speed;
                float direction2 = acceleration.x * direction.x + acceleration.y * direction.y;
                circles[fi].speed = circles[fi].speed - direction2 / float(std::pow(distance1, 2)) * direction;
                circles[si].speed = circles[si].speed + direction2 / float(std::pow(distance1, 2)) * direction;
            }
        }
    }

    for (size_t fi = 0; fi < circles.size(); ++fi)
    {
        sf::Vector2f position = circles[fi].shapes.getPosition();
        position += circles[fi].speed * dt;

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (circles[fi].speed.x > 0))
        {
            circles[fi].speed.x = -circles[fi].speed.x;
        }
        if ((position.x < 0) && (circles[fi].speed.x < 0))
        {
            circles[fi].speed.x = -circles[fi].speed.x;
        }
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (circles[fi].speed.y > 0))
        {
            circles[fi].speed.y = -circles[fi].speed.y;
        }
        if ((position.y < 0) && (circles[fi].speed.y < 0))
        {
            circles[fi].speed.y = -circles[fi].speed.y;
        }
        circles[fi].shapes.setPosition(position);
    }
}
void redrawFrame(sf::RenderWindow &window, std::vector<Circle> &circles)
{
    window.clear();
    for (size_t fi = 0; fi < circles.size(); ++fi)
    {
        window.draw(circles[fi].shapes);
    }
    window.display();
}
int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                            "Circles are moving towards screen", sf::Style::Default, settings);

    sf::Clock clock;
    std::vector<Circle> circles(5);
    init(circles);
    while (window.isOpen())
    {
        pollEvents(window);
        float dt = clock.restart().asSeconds();
        update(circles, dt);
        redrawFrame(window, circles);
    }
}
