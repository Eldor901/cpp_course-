#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>

struct Ball
{

    sf::CircleShape shape;
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
    std::uniform_int_distribution<unsigned> distribution(0, 1);
    return distribution(generator.engine);
}

float vectorLenght(sf::Vector2f &argument)
{
    return (pow((pow(argument.x, 2.0) + pow(argument.y, 2.0)), 0.5));
}

bool CreationOfBall(std::vector<Ball> &balls, sf::Vector2f click, const float BALL_SIZE)
{
    bool answer = true;
    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f delta = balls[i].shape.getPosition() - click;
        if (vectorLenght(delta) <= BALL_SIZE * 2)
        {
            answer = false;
        }
    }
    return answer;
}

void Init(std::vector<Ball> &balls, sf::Vector2f click, const float BALL_SIZE)
{
    if (CreationOfBall(balls, click, BALL_SIZE))
    {
        Ball space;
        balls.push_back(space);

        PRNG generator;
        initGenerator(generator);
        sf::Color color;

        size_t i = balls.size() - 1;
        float signX = Random(generator);
        float signY = Random(generator);
        float randomSpeedX = RandomSpeed(generator, 50, 250) * pow(-1.0, signX);
        float randomSpeedY = RandomSpeed(generator, 50, 250) * pow(-1.0, signY);
        balls[i].speed = {randomSpeedX, randomSpeedY};
        balls[i].shape.setRadius(BALL_SIZE);
        color.r = RandomColor(generator);
        color.b = RandomColor(generator);
        color.g = RandomColor(generator);
        balls[i].shape.setFillColor(color);
        balls[i].shape.setPosition({click});
    }
}

void pollEvents(sf::RenderWindow &window, std::vector<Ball> &balls, const float BALL_SIZE)
{
    sf::Vector2f click;
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonReleased:
            click = {float(event.mouseButton.x) - BALL_SIZE / 2, float(event.mouseButton.y) - BALL_SIZE / 2};
            Init(balls, click, BALL_SIZE);
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &balls)
{
    window.clear();
    for (size_t i = 0; i < balls.size(); ++i)
    {
        window.draw(balls[i].shape);
    }
    window.display();
}

float Len(sf::Vector2f speedVector, sf::Vector2f posVector)
{
    return ((speedVector.x * posVector.x) + (speedVector.y * posVector.y));
}

void update(std::vector<Ball> &balls, size_t fi, size_t si)
{
    sf::Vector2f deltaPos = balls[fi].shape.getPosition() - balls[si].shape.getPosition();
    sf::Vector2f deltaSpeed = balls[fi].speed - balls[si].speed;
    float speedX = balls[fi].speed.x - (Len(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.x;
    float speedY = balls[fi].speed.y - (Len(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.y;
    balls[fi].speed = {speedX, speedY};

    deltaPos = -deltaPos;
    deltaSpeed = -deltaSpeed;
    speedX = balls[si].speed.x - (Len(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.x;
    speedY = balls[si].speed.y - (Len(deltaSpeed, deltaPos) / pow(vectorLenght(deltaPos), 2.0)) * deltaPos.y;
    balls[si].speed = {speedX, speedY};
}
void BallColision(std::vector<Ball> &balls, const float BALL_SIZE)
{
    for (size_t fi = 0; fi < balls.size(); ++fi)
    {
        for (size_t si = fi + 1; si < balls.size(); ++si)
        {
            sf::Vector2f delta = balls[fi].shape.getPosition() - balls[si].shape.getPosition();
            if (vectorLenght(delta) <= BALL_SIZE * 2)
            {
                update(balls, fi, si);
            }
        }
    }
}

void checkCollision(const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT, const float BALL_SIZE, sf::Vector2f &speed, sf::Vector2f &position)
{
    if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed.x > 0))
    {
        speed.x = -speed.x;
    }
    if ((position.x < 0) && (speed.x < 0))
    {
        speed.x = -speed.x;
    }
    if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (speed.y > 0))
    {
        speed.y = -speed.y;
    }
    if ((position.y < 0) && (speed.y < 0))
    {
        speed.y = -speed.y;
    }
}

void update(const unsigned WINDOW_WIDTH, const unsigned WINDOW_HEIGHT, sf::Clock &clock, const float BALL_SIZE, std::vector<Ball> &balls)
{
    const float dt = clock.restart().asSeconds();
    BallColision(balls, BALL_SIZE);
    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f position = balls[i].shape.getPosition();

        checkCollision(WINDOW_WIDTH, WINDOW_HEIGHT, BALL_SIZE, balls[i].speed, position);

        balls[i].shape.setPosition(position + balls[i].speed * dt);
    }
}

int main()
{
    constexpr float BALL_SIZE = 40;
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clock;
    sf::Color color;

    std::vector<Ball> balls;

    while (window.isOpen())
    {
        pollEvents(window, balls, BALL_SIZE);
        update(WINDOW_WIDTH, WINDOW_HEIGHT, clock, BALL_SIZE, balls);
        redrawFrame(window, balls);
    }
}