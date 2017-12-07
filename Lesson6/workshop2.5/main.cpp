#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned BALL_SIZE = 40;
using namespace std;

struct Circle
{
    sf::CircleShape shapes;
    sf::Vector2f speed;
};
struct PRNG
{
    std::mt19937 engine;
};
void initGenerator(PRNG &generator)
{
    const unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}
float GetRandomSpeed(PRNG &generator, float minValue, float maxValue)
{
    std::uniform_real_distribution<float> distribution(minValue, maxValue);
    return distribution(generator.engine);
}
size_t GetRandomColor(PRNG &generator, size_t variable1, size_t variable2)
{
    std::uniform_int_distribution<size_t> distribution(variable1, variable2);
    return distribution(generator.engine);
}

void init(vector<Circle> &circles, sf::Vector2f &mousePosition)
{
    Circle circle;
    circles.push_back(circle);

    PRNG generator;
    initGenerator(generator);
    const float minAvalaibleSpeed = -200;
    const float maxAvalaibleSpeed = 200;
    sf::Color color;

    const vector<sf::Color> colors = {sf::Color(0, 0, 51),
                                      sf::Color(0, 204, 204),
                                      sf::Color(102, 0, 153),
                                      sf::Color(204, 51, 102),
                                      sf::Color(255, 255, 0),
                                      sf::Color(204, 255, 153),
                                      sf::Color(102, 0, 204),
                                      sf::Color(102, 0, 0)};
    size_t i = circles.size() - 1;

    float X = GetRandomSpeed(generator, minAvalaibleSpeed, maxAvalaibleSpeed);
    float Y = GetRandomSpeed(generator, minAvalaibleSpeed, maxAvalaibleSpeed);

    size_t j = GetRandomColor(generator, 0, 7);
    size_t k = GetRandomColor(generator, 0, 7);
    color.r = (colors[j].r + colors[k].r) / 2;
    color.b = (colors[j].b + colors[k].b) / 2;
    color.g = (colors[j].g + colors[k].g) / 2;

    circles[i].speed = {X, Y};
    circles[i].shapes.setPosition(mousePosition);
    circles[i].shapes.setRadius(BALL_SIZE);
    circles[i].shapes.setFillColor(color);
}

void onMouseClick(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}
bool checkNotOverlap(std::vector<Circle> &circles, sf::Vector2f &mousePosition)
{
    bool flag = true;
    for (size_t j = 0; j < circles.size(); ++j)
    {
        sf::Vector2f deltaVector = circles[j].shapes.getPosition() - mousePosition;
        float delta = std::sqrt(std::pow(deltaVector.x, 2) + std::pow(deltaVector.y, 2));
        if (delta <= 2 * BALL_SIZE)
        {
            flag = false;
        }
    }
    return flag;
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, vector<Circle> &circles)
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMouseClick(event.mouseButton, mousePosition);
            if (checkNotOverlap(circles, mousePosition) || (circles.size() == 0))
            {
                init(circles, mousePosition);
            }
            break;
        default:
            break;
        }
    }
}

void update(vector<Circle> &circles, float &dt)
{
    for (size_t i = 0; i < circles.size(); ++i)
    {
        for (size_t j = i + 1; j < circles.size(); ++j)
        {
            sf::Vector2f direction = circles[i].shapes.getPosition() - circles[j].shapes.getPosition();
            float distance1 = std::sqrt(std::pow(direction.x, 2) + std::pow(direction.y, 2));
            float distance2 = 2 * BALL_SIZE;
            if (distance1 <= distance2)
            {
                sf::Vector2f acceleration = circles[i].speed - circles[j].speed;
                float direction2 = acceleration.x * direction.x + acceleration.y * direction.y;
                circles[i].speed = circles[i].speed - direction2 / float(std::pow(distance1, 2)) * direction;
                circles[j].speed = circles[j].speed + direction2 / float(std::pow(distance1, 2)) * direction;
            }
        }
    }

    for (size_t i = 0; i < circles.size(); ++i)
    {
        sf::Vector2f position = circles[i].shapes.getPosition();
        position += circles[i].speed * dt;

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (circles[i].speed.x > 0))
        {
            circles[i].speed.x = -circles[i].speed.x;
        }
        if ((position.x < 0) && (circles[i].speed.x < 0))
        {
            circles[i].speed.x = -circles[i].speed.x;
        }
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (circles[i].speed.y > 0))
        {
            circles[i].speed.y = -circles[i].speed.y;
        }
        if ((position.y < 0) && (circles[i].speed.y < 0))
        {
            circles[i].speed.y = -circles[i].speed.y;
        }
        circles[i].shapes.setPosition(position);
    }
}
void redrawFrame(sf::RenderWindow &window, std::vector<Circle> &circles)
{
    window.clear();
    for (size_t i = 0; i < 5; ++i)
    {
        window.draw(circles[i].shapes);
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
    sf::Vector2f mousePosition;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition, circles);
        float dt = clock.restart().asSeconds();
        update(circles, dt);
        redrawFrame(window, circles);
    }
}
