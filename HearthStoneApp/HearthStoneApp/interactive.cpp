#pragma once
#include "interactive.h"

Interactive::Interactive(sf::Vector2f _position, sf::Vector2f _size, std::shared_ptr<GameHandler> _gameHandler) {
	body = sf::RectangleShape(_size);
	body.setPosition(_position);

	gameHandler = std::shared_ptr<GameHandler>(_gameHandler);
}

void Interactive::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	gameHandler->getWindowPtr()->draw(body);
}

bool Interactive::isCursorHoverdOver() const {
	if (body.getGlobalBounds().contains(gameHandler->getMousePosition())) return true;
	else return false;
}

bool Interactive::isItClicked() const {
	if (gameHandler->isMouseClicked() && isCursorHoverdOver()) return true;
	else return false;
}