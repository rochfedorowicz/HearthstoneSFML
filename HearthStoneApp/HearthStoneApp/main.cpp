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
    gameHandlerPtr->getDataHandlerPtr()->loadTextures("Textures");
    gameHandlerPtr->getDataHandlerPtr()->loadFonts("Fonts");
    gameHandlerPtr->manageWindow();

    return 0;
}
