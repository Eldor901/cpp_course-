#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <random>
#include <ctime>
constexpr float BALL_SIZE = 40;
constexpr int BALLS_COUNT = 5;
constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

struct Ball
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

unsigned RandomSpeed(PRNG &generator, unsigned minValue, unsigned maxValue)
{
    std::uniform_int_distribution<unsigned> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

unsigned RandomColor(PRNG &generator)
{
    std::uniform_int_distribution<unsigned> distribution(0, 255);
    return distribution(generator.engine);
}

unsigned Random(PRNG &generator)
{
    std::uniform_int_distribution<unsigned> distribution(0, 0);
    return distribution(generator.engine);
}

void init(std::vector<Ball> &balls, const float BALL_SIZE)
{
    PRNG generator;
    initGenerator(generator);
    sf::Color color;

    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        float signX = Random(generator);
        float signY = Random(generator);
        float randomSpeedX = RandomSpeed(generator, 100, 200) * pow(1.0, signX);
        float randomSpeedY = RandomSpeed(generator, 100, 200) * pow(1.0, signY);
        balls[fi].speed = {randomSpeedX, randomSpeedY};
        balls[fi].shapes.setRadius(BALL_SIZE);
        color.r = RandomColor(generator);
        color.b = RandomColor(generator);
        color.g = RandomColor(generator);
        balls[fi].shapes.setFillColor(color);
    }

    balls[0].shapes.setPosition({100, 300});
    balls[1].shapes.setPosition({300, 300});
    balls[2].shapes.setPosition({400, 300});
    balls[3].shapes.setPosition({600, 300});
    balls[4].shapes.setPosition({700, 300});
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &balls)
{
    window.clear();
    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        window.draw(balls[fi].shapes);
    }
    window.display();
}

float Lenth(sf::Vector2f &argument)
{
    return (pow((pow(argument.x, 2.0) + pow(argument.y, 2.0)), 0.5));
}

float Len(sf::Vector2f speedVector, sf::Vector2f posVector)
{
    return ((speedVector.x * posVector.x) + (speedVector.y * posVector.y));
}

void speedUpdate(std::vector<Ball> &balls, size_t fi, size_t si)
{
    sf::Vector2f deltaPos = balls[fi].shapes.getPosition() - balls[si].shapes.getPosition();
    sf::Vector2f deltaSpeed = balls[fi].speed - balls[si].speed;
    float speedX = balls[fi].speed.x - (Len(deltaSpeed, deltaPos) / pow(Lenth(deltaPos), 2.0)) * deltaPos.x;
    float speedY = balls[fi].speed.y - (Len(deltaSpeed, deltaPos) / pow(Lenth(deltaPos), 2.0)) * deltaPos.y;
    balls[fi].speed = {speedX, speedY};

    deltaPos = -deltaPos;
    deltaSpeed = -deltaSpeed;
    speedX = balls[si].speed.x - (Len(deltaSpeed, deltaPos) / pow(Lenth(deltaPos), 2.0)) * deltaPos.x;
    speedY = balls[si].speed.y - (Len(deltaSpeed, deltaPos) / pow(Lenth(deltaPos), 2.0)) * deltaPos.y;
    balls[si].speed = {speedX, speedY};
}

void checkColision(std::vector<Ball> &balls, const float BALL_SIZE)
{
    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        for (size_t si = fi + 1; si < balls.size(); ++si)
        {
            sf::Vector2f delta = balls[fi].shapes.getPosition() - balls[si].shapes.getPosition();
            if (Lenth(delta) <= BALL_SIZE * 2)
            {
                speedUpdate(balls, fi, si);
            }
        }
    }
}

void update(const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT, const float dt, const float BALL_SIZE, std::vector<Ball> &balls)
{
    checkColision(balls, BALL_SIZE);
    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f position = balls[i].shapes.getPosition();

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (balls[i].speed.x > 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.x < 0) && (balls[i].speed.x < 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (balls[i].speed.y > 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if ((position.y < 0) && (balls[i].speed.y < 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        balls[i].shapes.setPosition(position + balls[i].speed * dt);
    }
}

int main()
{

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clock;

    std::vector<Ball> balls(BALLS_COUNT);

    init(balls, BALL_SIZE);

    while (window.isOpen())
    {
        pollEvents(window);
        const float dt = clock.restart().asSeconds();
        update(WINDOW_WIDTH, WINDOW_HEIGHT, dt, BALL_SIZE, balls);
        redrawFrame(window, balls);
    }
}