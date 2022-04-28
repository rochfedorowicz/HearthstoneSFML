#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "button.h"
#include "callbacks.h"
#include "gameHandler.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(640, 480), "This app", sf::Style::Titlebar);
    GameHandler gameHandler(&window);
    gameHandler.loadFont("C:/Windows/Fonts/calibri.ttf", "Calibri");
    sf::Font a = gameHandler.getFontByName("Calibri");
    Button newButton(sf::Vector2f(120, 80), sf::Vector2f(400, 50), sf::Color::White, "Display 1", a, sf::Color::Black, &callbacks::fn, &window);
    Button newButton2(sf::Vector2f(120, 180), sf::Vector2f(400, 50), sf::Color::White, "Display 1", a, sf::Color::Black, &callbacks::fn, &window);
    Button newButton3(sf::Vector2f(120, 280), sf::Vector2f(400, 50), sf::Color::White, "Exit", a, sf::Color::Black, &callbacks::shutDown, &window);
    Button buttons[3] = { newButton, newButton2, newButton3 };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed) {
                for (auto& button : buttons) {
                    if (button.getBody().getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) button.callback();
                }
            }
        }
        window.clear();
        for (auto& button : buttons) {
            window.draw(button);
        }
        window.display();
    }
    return 0;
}
