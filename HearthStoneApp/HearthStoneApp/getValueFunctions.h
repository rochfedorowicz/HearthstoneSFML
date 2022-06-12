#pragma once
#ifndef GET_VALUE_FUNCTIONS
#define GET_VALUE_FUNCTIONS
#include "Handlers/gameHandler.h"

namespace getValueFunctions {

	int getValueByPlayersMana(std::shared_ptr<GameHandler> _gameHandler);

	int getMaxValueByPlayersMana(std::shared_ptr<GameHandler> _gameHandler);

	int getValueByOpponentsMana(std::shared_ptr<GameHandler> _gameHandler);

	int getMaxValueByOpponentsMana(std::shared_ptr<GameHandler> _gameHandler);

	int getValueByRoundsTimer(std::shared_ptr<GameHandler> _gameHandler);

	int getMaxValueByRoundsTimer(std::shared_ptr<GameHandler> _gameHandler);

	std::string getRoundsOwner(std::shared_ptr<GameHandler> _gameHandler);
}

#endif
