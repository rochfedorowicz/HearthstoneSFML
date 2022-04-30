#pragma once
#include "callbacks.h"


void callbacks::fn(std::shared_ptr<sf::RenderWindow> ptr) {
    std::cout << " " << 1;
}

void callbacks::shutDown(std::shared_ptr<sf::RenderWindow> ptr) {
    ptr->close();
}