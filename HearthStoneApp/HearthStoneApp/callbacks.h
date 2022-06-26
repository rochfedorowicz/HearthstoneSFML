#pragma once
#ifndef CALLBACKS
#define CALLBACKS
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Handlers/gameHandler.h"

/** All available callback functions used by buttons. */
namespace callbacks {

    /** Prints "1" to the console. */
    void testFn(std::shared_ptr<GameHandler> _gameHandler);

    /** Shuts down curent window. */
    void shutDown(std::shared_ptr<GameHandler> _gameHandler);

	/** Playing game. */
	void playGame(std::shared_ptr<GameHandler> _gameHandler);

	/** Displaying main menu. */
	void displayMenu(std::shared_ptr<GameHandler> _gameHandler);

	/** Displaying settings. */
	void displaySettings(std::shared_ptr<GameHandler> _gameHandler);

	/** Changing resolution to 1920 x 1080. */
	void changeResolutionTo1920x1080(std::shared_ptr<GameHandler> _gameHandler);

	/** Changing resolution to 1280 x 720. */
	void changeResolutionTo1280x720(std::shared_ptr<GameHandler> _gameHandler);

	/** Skipping round of current player. */
	void skipRound(std::shared_ptr<GameHandler> _gameHandler);

	/** Displaying name input's menu and asking for names. */
	void proceedToGamePlay(std::shared_ptr<GameHandler> _gameHandler);
}
#endif
