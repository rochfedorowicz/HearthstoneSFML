#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Button.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "SFML works!");
    Button newButton(sf::Vector2f(120, 50), sf::Color::Cyan, &window);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(newButton);
        window.display();
    }
    return 0;
}
