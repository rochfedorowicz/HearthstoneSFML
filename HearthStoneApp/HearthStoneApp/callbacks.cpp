#include "callbacks.h"


void callbacks::fn(std::shared_ptr<GameHandler> ptr) {
    std::cout << " " << 1;
}

void callbacks::shutDown(std::shared_ptr<GameHandler> ptr) {
    ptr->getWindowPtr()->close();
}