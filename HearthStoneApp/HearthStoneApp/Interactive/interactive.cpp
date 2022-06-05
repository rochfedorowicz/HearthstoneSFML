#pragma once
#include "interactive.h"

Interactive::Interactive(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::shared_ptr<GameHandler> _gameHandler)
	: UpdatableRect(_position, _size, _color, _gameHandler) {
	body.setOutlineColor(sf::Color(32, 230, 32, 200));
}

bool Interactive::isCursorHoverdOver() const {
	if (body.getGlobalBounds().contains(gameHandler->getMousePosition())) return true;
	else return false;
}

bool Interactive::isItClicked() const {
	if (gameHandler->isMouseClicked() && isCursorHoverdOver()) return true;
	else return false;
}

void Interactive::update() {
	if (isCursorHoverdOver()) body.setOutlineThickness(3);
	else body.setOutlineThickness(0);
	UpdatableRect::update();
}