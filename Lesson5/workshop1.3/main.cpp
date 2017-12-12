#include <SFML/Graphics.hpp>
using namespace sf;

void init(Texture &texture, Sprite &cat)
{
    texture.loadFromFile("workshop1.3/cat.png");
    cat.setTexture(texture);
    cat.setPosition(100, 500);
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
void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(cat);
    window.display();
}

int main()
{
    constexpr unsigned WIDTH = 800;
    constexpr unsigned HEIGHT = 600;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "loading a cat");
    sf::Texture texture;
    sf::Sprite cat;
    init(texture, cat);

    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, cat);
    }
}
