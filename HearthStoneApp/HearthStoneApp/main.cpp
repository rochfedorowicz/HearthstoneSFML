#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "gameHandler.h"
#include "interactive.h"
#include "button.h"
#include "card.h"
#include "callbacks.h"

int main() {

    std::shared_ptr<GameHandler> gameHandlerPtr = std::make_shared<GameHandler>();
    std::shared_ptr <sf::Texture> newTexture = std::make_shared<sf::Texture>();
    newTexture->loadFromFile("cardTexture.png");
    gameHandlerPtr->loadFont("C:/Windows/Fonts/calibri.ttf", "Calibri");
    gameHandlerPtr->appendDrawable(std::make_shared<Button>(sf::Vector2f(120, 80), sf::Vector2f(400, 50), sf::Color::White, "Display 1",
        gameHandlerPtr->getFontPtrByName("Calibri"), sf::Color::Black, CallbacksEnum::TEST_FN, gameHandlerPtr));
    gameHandlerPtr->appendDrawable(std::make_shared<Button>(sf::Vector2f(120, 180), sf::Vector2f(400, 50), sf::Color::White, "Display 1",
        gameHandlerPtr->getFontPtrByName("Calibri"), sf::Color::Black, CallbacksEnum::TEST_FN, gameHandlerPtr));
    gameHandlerPtr->appendDrawable(std::make_shared<Button>(sf::Vector2f(120, 280), sf::Vector2f(400, 50), sf::Color::White, "Exit",
        gameHandlerPtr->getFontPtrByName("Calibri"), sf::Color::Black, CallbacksEnum::SHUT_DOWN, gameHandlerPtr));
    gameHandlerPtr->appendDrawable(std::make_shared<Card>(newTexture, gameHandlerPtr));
    gameHandlerPtr->manageWindow();


    return 0;
}
