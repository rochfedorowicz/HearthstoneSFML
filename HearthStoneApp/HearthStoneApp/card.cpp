#pragma once
#include "card.h"

void Card::update() {
	Interactive::update();
	gameHandler->getWindowPtr()->draw(texture);
	if (isItClicked()) {
		shouldBeDragged = true;
		differenceOfDrag = gameHandler->getMousePosition() - body.getPosition();
	}
	if (shouldBeDragged && gameHandler->isMousePressed()) {
		move(gameHandler->getMousePosition() - differenceOfDrag);
	}
	else shouldBeDragged = false;
}

Card::Card(std::shared_ptr<sf::Texture> _texture, std::shared_ptr<GameHandler> _gameHandler) 
	: Interactive(sf::Vector2f(2, 2), sf::Vector2f(_texture->getSize()), _gameHandler) {
	texture = sf::Sprite(*_texture);
	texture.setPosition(sf::Vector2f(2, 2));
}

void Card::move(sf::Vector2f _change) {
	body.setPosition(_change);
	texture.setPosition(_change);
}