#pragma once
#ifndef CALLBACKS
#define CALLBACKS
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Handlers/gameHandler.h"

//All available callback functions
namespace callbacks {

    //Print "1" to the console
    void fn(std::shared_ptr<sf::RenderWindow> ptr);

    //Shuts window down
    void shutDown(std::shared_ptr<sf::RenderWindow> ptr);
}

#endif
