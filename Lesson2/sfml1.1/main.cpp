#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Traffic Light");
    window.clear(sf::Color::White);

    sf::RectangleShape shape1;
    shape1.setSize({200, 500});
    shape1.setPosition({300, 50});
    shape1.setFillColor(sf::Color(128, 128, 128));
    window.draw(shape1);

    sf::CircleShape shape2(70);
    shape2.setPosition({330, 70});
    shape2.setFillColor(sf::Color(0, 255, 0));
    window.draw(shape2);

    sf::CircleShape shape3(70);
    shape2.setPosition({330, 230});
    shape2.setFillColor(sf::Color::Yellow);
    window.draw(shape2);

    sf::CircleShape shape4(70);
    shape2.setPosition({330, 395});
    shape2.setFillColor(sf::Color::Red);
    window.draw(shape2);

    window.display();
    sf::sleep(sf::seconds(6));
}