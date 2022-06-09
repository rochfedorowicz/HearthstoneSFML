#pragma once
#ifndef CALLBACKS
#define CALLBACKS
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Handlers/gameHandler.h"

//All available callback functions
namespace callbacks {

    //Print "1" to the console
    void testFn(std::shared_ptr<GameHandler> _gameHandler);

    //Shuts window down
    void shutDown(std::shared_ptr<GameHandler> _gameHandler);

	void playGame(std::shared_ptr<GameHandler> _gameHandler);

	void displayMenu(std::shared_ptr<GameHandler> _gameHandler);

	void displaySettings(std::shared_ptr<GameHandler> _gameHandler);

	void changeResolutionTo1920x1080(std::shared_ptr<GameHandler> _gameHandler);

	void changeResolutionTo1280x720(std::shared_ptr<GameHandler> _gameHandler);
}
#endif
