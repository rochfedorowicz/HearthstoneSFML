#pragma once
#include "roundsTimeBar.h"

RoundsTimeBar::RoundsTimeBar(sf::Vector2f _position, sf::Vector2f _size, BarType _type, std::shared_ptr<GameHandler> _gameHandler)
	: UpdatableBar(_position, _size, sf::Color::Black, sf::Color::Green, _gameHandler->getRoundHandlerPtr()->getMaxSecondsInRound(), _type, _gameHandler) {}

void RoundsTimeBar::update() {
	changeValue(gameHandler->getRoundHandlerPtr()->getCurrentSecondsInRound());
	UpdatableBar::update();
}

bool RoundsTimeBar::shouldBeDestroyed() {
	return false;
}