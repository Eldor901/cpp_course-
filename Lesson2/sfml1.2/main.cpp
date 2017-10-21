#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
int main()
{
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "ELDOR ERGASHEV SHUKXRATO'GLI");
    window.clear(sf::Color(224, 255, 255));

    sf::RectangleShape shape1;
    shape1.setSize({200, 30});
    shape1.setPosition({220, 450});
    shape1.setRotation({180});
    shape1.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({300, 30});
    shape2.setPosition({40, 150});
    shape2.setRotation({90});
    shape2.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({200, 30});
    shape3.setPosition({220, 300});
    shape3.setRotation({180});
    shape3.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({200, 30});
    shape4.setPosition({220, 180});
    shape4.setRotation({180});
    shape4.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape4);

    sf::RectangleShape shape5;
    shape5.setSize({200, 30});
    shape5.setPosition({460, 450});
    shape5.setRotation({180});
    shape5.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape5);

    sf::RectangleShape shape6;
    shape6.setSize({300, 30});
    shape6.setPosition({260, 150});
    shape6.setRotation({90});
    shape6.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape6);

    sf::RectangleShape shape7;
    shape7.setSize({200, 30});
    shape7.setPosition({460, 300});
    shape7.setRotation({180});
    shape7.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape7);

    sf::RectangleShape shape8;
    shape8.setSize({200, 30});
    shape8.setPosition({460, 180});
    shape8.setRotation({180});
    shape8.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape8);

    sf::RectangleShape shape9;
    shape9.setSize({200, 30});
    shape9.setPosition({700, 180});
    shape9.setRotation({180});
    shape9.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape9);

    sf::RectangleShape shape10;
    shape10.setSize({350, 30});
    shape10.setPosition({500, 150});
    shape10.setRotation({50});
    shape10.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape10);

    sf::RectangleShape shape11;
    shape11.setSize({230, 30});
    shape11.setPosition({720, 450});
    shape11.setRotation({180});
    shape11.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape11);

    sf::RectangleShape shape12;
    shape12.setSize({300, 30});
    shape12.setPosition({820, 150});
    shape12.setRotation({90});
    shape12.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape12);

    sf::RectangleShape shape13;
    shape13.setSize({250, 30});
    shape13.setPosition({1060, 300});
    shape13.setRotation({180});
    shape13.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape13);

    sf::RectangleShape shape14;
    shape14.setSize({300, 30});
    shape14.setPosition({1060, 150});
    shape14.setRotation({90});
    shape14.setFillColor(sf::Color(139, 0, 0));
    window.draw(shape14);
    window.display();
    sf::sleep(sf::seconds(6));
}
