#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "gameHandler.h"
#include "interactive.h"
#include "button.h"
#include "card.h"
#include "callbacks.h"
#include "buttonBlueprint.h"

int main() {

    std::shared_ptr<GameHandler> gameHandlerPtr = std::make_shared<GameHandler>();
    gameHandlerPtr->loadTexture("cardTexture.png", "ct");
    gameHandlerPtr->loadFont("C:/Windows/Fonts/calibri.ttf", "Calibri");
    gameHandlerPtr->loadFont("C:/Windows/Fonts/MATURASC.TTF", "Matura");
    gameHandlerPtr->manageWindow();


    return 0;
}
