#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "gameHandler.h"

//All available callback functions
namespace callbacks {

    void fn(std::shared_ptr<GameHandler> ptr);

    //Shuts window down
    void shutDown(std::shared_ptr<GameHandler> ptr);
}