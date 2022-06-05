#include "getValueFunctions.h"

int getValueFunctions::getValueByPlayersMana(std::shared_ptr<GameHandler> _gameHandler) {
    return _gameHandler->getPlayerPtr()->getCurrentMana();
}

int getValueFunctions::getMaxValueByPlayersMana(std::shared_ptr<GameHandler> _gameHandler) {
    return _gameHandler->getPlayerPtr()->getMaxMana();
}

int getValueFunctions::getValueByRoundsTimer(std::shared_ptr<GameHandler> _gameHandler) {
    return _gameHandler->getRoundHandlerPtr()->getCurrentSecondsInRound();
}

int getValueFunctions::getMaxValueByRoundsTimer(std::shared_ptr<GameHandler> _gameHandler) {
    return _gameHandler->getRoundHandlerPtr()->getMaxSecondsInRound();
}