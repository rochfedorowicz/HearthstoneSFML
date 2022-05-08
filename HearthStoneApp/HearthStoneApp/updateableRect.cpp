#pragma once
#include "updateableRect.h"

UpdatableRect::UpdatableRect(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::shared_ptr<GameHandler> _gameHandler) {
	body = sf::RectangleShape(_size);
	body.setPosition(_position);
	body.setFillColor(_color);

	gameHandler = std::shared_ptr<GameHandler>(_gameHandler);
}

void UpdatableRect::update() {
	gameHandler->getWindowPtr()->draw(body);
}