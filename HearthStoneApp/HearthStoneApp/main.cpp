#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "button.h"
#include "callbacks.h"
#include "gameHandler.h"

int main()
{

    GameHandler gameHandler;
    gameHandler.loadFont("C:/Windows/Fonts/calibri.ttf", "Calibri");
    Button newButton(sf::Vector2f(120, 80), sf::Vector2f(400, 50), sf::Color::White, "Display 1",
        gameHandler.getFontPtrByName("Calibri"), sf::Color::Black, &callbacks::fn, gameHandler);
    Button newButton2(sf::Vector2f(120, 180), sf::Vector2f(400, 50), sf::Color::White, "Display 1",
        gameHandler.getFontPtrByName("Calibri"), sf::Color::Black, &callbacks::fn, gameHandler);
    Button newButton3(sf::Vector2f(120, 280), sf::Vector2f(400, 50), sf::Color::White, "Exit",
        gameHandler.getFontPtrByName("Calibri"), sf::Color::Black, &callbacks::shutDown, gameHandler);
    Button buttons[3] = { newButton, newButton2, newButton3 };

    while (gameHandler.getWindowPtr()->isOpen())
    {
        sf::Event event;
        while (gameHandler.getWindowPtr()->pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed) {
                for (auto& button : buttons) {
                    if (button.getBody().getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) button.callback();
                }
            }
        }
        gameHandler.getWindowPtr()->clear();
        for (auto& button : buttons) {
            gameHandler.getWindowPtr()->draw(button);
        }
        gameHandler.getWindowPtr()->display();
    }
    return 0;
}
