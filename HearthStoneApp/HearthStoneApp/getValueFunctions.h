#pragma once
#ifndef GET_VALUE_FUNCTIONS
#define GET_VALUE_FUNCTIONS
#include "Handlers/gameHandler.h"

/** All possible getting value function's. */
namespace getValueFunctions {

	/** Getter for current amount of player's mana. */
	int getValueByPlayersMana(std::shared_ptr<GameHandler> _gameHandler);

	/** Getter for maximum amount of player's mana. */
	int getMaxValueByPlayersMana(std::shared_ptr<GameHandler> _gameHandler);

	/** Getter for current amount of opponent's mana. */
	int getValueByOpponentsMana(std::shared_ptr<GameHandler> _gameHandler);

	/** Getter for maximum amount of opponent's mana. */
	int getMaxValueByOpponentsMana(std::shared_ptr<GameHandler> _gameHandler);

	/** Getter for number of seconds in current round. */
	int getValueByRoundsTimer(std::shared_ptr<GameHandler> _gameHandler);

	/** Getter for round's length in seconds. */
	int getMaxValueByRoundsTimer(std::shared_ptr<GameHandler> _gameHandler);

	/** Getter for round's owner player's name */
	std::string getRoundsOwner(std::shared_ptr<GameHandler> _gameHandler);

	/** Getter for game's winner player's name */
	std::string getRoundsWinner(std::shared_ptr<GameHandler> _gameHandler);
}

#endif
