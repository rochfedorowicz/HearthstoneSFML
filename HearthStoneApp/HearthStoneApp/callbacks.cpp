#pragma once
#include "callbacks.h"


void callbacks::testFn(std::shared_ptr<GameHandler> _gameHandler) {
	std::cout << "1 ";
}

void callbacks::shutDown(std::shared_ptr<GameHandler> _gameHandler) {
	_gameHandler->setGameState(GameStateEnum::NONE);
	_gameHandler->getWindowPtr()->close();
}

void callbacks::playGame(std::shared_ptr<GameHandler> _gameHandler) {
	if (*_gameHandler->getPlayerPtr()->getPointerToName() != "" &&
		*_gameHandler->getOpponentPtr()->getPointerToName() != "") {
		_gameHandler->setGameState(GameStateEnum::PLAY);
		_gameHandler->getWindowPtr()->close();
	}
}

void callbacks::displayMenu(std::shared_ptr<GameHandler> _gameHandler) {
	_gameHandler->setGameState(GameStateEnum::MENU);
	_gameHandler->getWindowPtr()->close();
}

void callbacks::displaySettings(std::shared_ptr<GameHandler> _gameHandler) {
	_gameHandler->setGameState(GameStateEnum::SETTINGS);
	_gameHandler->getWindowPtr()->close();
}

void callbacks::changeResolutionTo1920x1080(std::shared_ptr<GameHandler> _gameHandler) {
	_gameHandler->setGameResolution(sf::Vector2i(1920, 1080));
}

void callbacks::changeResolutionTo1280x720(std::shared_ptr<GameHandler> _gameHandler) {
	_gameHandler->setGameResolution(sf::Vector2i(1280, 720));
}

void callbacks::skipRound(std::shared_ptr<GameHandler> _gameHandler) {
	_gameHandler->getRoundHandlerPtr()->changeTurn();
	if (_gameHandler->getRoundHandlerPtr()->getTurnOrder() == Turn::PLAYERS_TURN) _gameHandler-> getPlayerPtr()->renewMana();
	else _gameHandler->getOpponentPtr()->renewMana();
	_gameHandler->getRoundHandlerPtr()->restartRound();
	_gameHandler->setHasJustFinished(true);
}

void callbacks::proceedToGamePlay(std::shared_ptr<GameHandler> _gameHandler) {
	_gameHandler->setGameState(GameStateEnum::PREPARING);
	_gameHandler->getWindowPtr()->close();
}