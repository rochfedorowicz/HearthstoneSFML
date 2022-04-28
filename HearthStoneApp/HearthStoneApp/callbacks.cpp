#include "callbacks.h"

void callbacks::fn(sf::RenderWindow* ptr) {
    std::cout << " " << 1;
}

void callbacks::shutDown(sf::RenderWindow* windowPtr) {
    windowPtr->close();
}