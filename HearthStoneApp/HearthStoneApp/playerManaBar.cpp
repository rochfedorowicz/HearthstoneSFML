#pragma once
#include "playerManaBar.h"

PlayerManaBar::PlayerManaBar(sf::Vector2f _position, sf::Vector2f _size, BarType _type, std::shared_ptr<GameHandler> _gameHandler) 
	: UpdatableBar(_position, _size, sf::Color::Black, sf::Color::Blue, _gameHandler->getPlayerPtr()->getMaxMana(), _type, _gameHandler) {}

void PlayerManaBar::update() {
	changeValue(gameHandler->getPlayerPtr()->getCurrentMana());
	UpdatableBar::update();
}

bool PlayerManaBar::shouldBeDestroyed() {
	return false;
}