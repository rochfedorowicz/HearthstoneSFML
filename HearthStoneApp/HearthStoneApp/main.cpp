#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <filesystem>
#include "Handlers/gameHandler.h"
#include "Interactive/interactive.h"
#include "Interactive/button.h"
#include "Cards/card.h"
#include "callbacks.h"
#include "buttonBlueprint.h"


#include <iostream>
#include <string>
#include <regex>

int main() {

    std::shared_ptr<GameHandler> gameHandlerPtr = std::make_shared<GameHandler>();
    gameHandlerPtr->getDataHandlerPtr()->loadTextures("Textures\\1920x1080");
    gameHandlerPtr->getDataHandlerPtr()->getLoadedTexturesResolution() = sf::Vector2i(1920, 1080);
    gameHandlerPtr->getDataHandlerPtr()->loadFonts("Fonts");
    
    gameHandlerPtr->manageWindow();

    return 0;
}
