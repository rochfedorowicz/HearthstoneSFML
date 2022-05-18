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

bool UpdatableRect::shouldBeDestroyed() {
	return false;
}

sf::Vector2f UpdatableRect::getCenterOfBody() {
	return sf::Vector2f(body.getGlobalBounds().left + body.getGlobalBounds().width / 2,
		body.getGlobalBounds().top + body.getGlobalBounds().height / 2);
}