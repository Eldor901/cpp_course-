#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
int main()
{

    sf::RectangleShape shape1;
    shape1.setSize({500, 300});
    shape1.setPosition({80, 300});
    shape1.setFillColor(sf::Color(139, 69, 19));

    sf::RectangleShape shape2;
    shape2.setSize({80, 200});
    shape2.setPosition({110, 400});
    shape2.setFillColor(sf::Color(80, 80, 80));

    sf::ConvexShape shape3;
    shape3.setFillColor(sf::Color(128, 0, 0));
    shape3.setPosition({325, 200});
    shape3.setPointCount(4);
    shape3.setPoint(0, {-120, 0});
    shape3.setPoint(1, {120, 0});
    shape3.setPoint(2, {300, 120});
    shape3.setPoint(3, {-300, 120});

    sf::RectangleShape shape4;
    shape4.setSize({40, 100});
    shape4.setPosition({380, 150});
    shape4.setFillColor(sf::Color(80, 80, 80));

    sf::RectangleShape shape5;
    shape5.setSize({60, 40});
    shape5.setPosition({370, 150});
    shape5.setFillColor(sf::Color(80, 80, 80));

    sf::CircleShape shape6(20);
    shape6.setPosition({390, 115});
    shape6.setFillColor(sf::Color(150, 150, 150));

    sf::CircleShape shape7(25);
    shape7.setPosition({395, 80});
    shape7.setFillColor(sf::Color(150, 150, 150));

    sf::CircleShape shape8(30);
    shape8.setPosition({410, 50});
    shape8.setFillColor(sf::Color(150, 150, 150));

    sf::CircleShape shape9(35);
    shape9.setPosition({430, 20});
    shape9.setFillColor(sf::Color(150, 150, 150));

    sf::RenderWindow window(sf::VideoMode({800, 600}), "Little House");

    window.clear(sf::Color(255, 255, 255));
    window.draw(shape1);
    window.draw(shape2);
    window.draw(shape3);
    window.draw(shape4);
    window.draw(shape5);
    window.draw(shape6);
    window.draw(shape7);
    window.draw(shape8);
    window.draw(shape9);

    window.display();

    sf::sleep(sf::seconds(6));
}

