#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void init(sf::Texture &texture, sf::Sprite &cat, sf::Texture &textpointer, sf::Sprite &pointer)
{
    texture.loadFromFile("cat.png");
    cat.setTexture(texture);
    cat.setPosition(100, 500);
    cat.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

    textpointer.loadFromFile("pointer.png");
    pointer.setTexture(textpointer);
    pointer.setPosition(100, 500);
    pointer.setOrigin(textpointer.getSize().x / 2, textpointer.getSize().y / 2);
}
void onMouseClick(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition)
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
        case sf::Event::MouseButtonPressed:
            onMouseClick(event.mouseButton, mousePosition);
            break;
        default:
            break;
        }
    }
}
void update(const sf::Vector2f &mousePosition, sf::Sprite &cat, sf::Sprite &pointer, float &dt)
{
    const sf::Vector2f delta = mousePosition - cat.getPosition();
    if (delta.x > 0)
    {
        cat.setScale(1, 1);
    }
    if (delta.x < 0)
    {
        cat.setScale(-1, 1);
    }
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    if ((delta.x != 0) && (delta.y != 0))
    {
        sf::Vector2f direction = {delta.x / distance,
                                  delta.y / distance};
        float speed = std::min(distance, 200.f * dt);
        sf::Vector2f move = direction * speed;
        cat.setPosition(cat.getPosition() + move);
    }
    pointer.setPosition(mousePosition);
}

void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &pointer)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(cat);
    window.draw(pointer);
    window.display();
}

int main()
{
    constexpr unsigned WIDTH = 800;
    constexpr unsigned HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Moving towards pointer ");
    sf::Clock clock;

    sf::Texture texture;
    sf::Sprite cat;

    sf::Texture textpointer;
    sf::Sprite pointer;

    sf::Vector2f mousePosition = {100, 500};
    init(texture, cat, textpointer, pointer);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        float dt = clock.restart().asSeconds();
        update(mousePosition, cat, pointer, dt);
        redrawFrame(window, cat, pointer);
    }
}
