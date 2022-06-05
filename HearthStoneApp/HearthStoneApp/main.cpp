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


int main() {

    std::shared_ptr<GameHandler> gameHandlerPtr = std::make_shared<GameHandler>();
    auto texturesDir = std::filesystem::current_path();
    texturesDir += "\\Textures";
    for (auto const& textureDir : std::filesystem::directory_iterator{ texturesDir })
    {
        gameHandlerPtr->loadTexture(textureDir.path().string(), textureDir.path().filename().string().erase(textureDir.path().filename().string().find('.')));
    }

    texturesDir = std::filesystem::current_path();
    texturesDir += "\\Fonts";
    for (auto const& textureDir : std::filesystem::directory_iterator{ texturesDir })
    {
        gameHandlerPtr->loadFont(textureDir.path().string(), textureDir.path().filename().string().erase(textureDir.path().filename().string().find('.')));
    }
    gameHandlerPtr->manageWindow();


    return 0;
}
