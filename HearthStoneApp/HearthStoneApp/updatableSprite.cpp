#pragma once
#include "updatableSprite.h"

UpdatableSprite::UpdatableSprite(sf::Vector2f _position, sf::Vector2f _size, std::string _textureName, std::shared_ptr<GameHandler> _gameHandler) {
	spriteToDisplay = sf::Sprite(*_gameHandler->getTexturePtrByName(_textureName),
		sf::IntRect(static_cast<sf::Vector2i>(_position), static_cast<sf::Vector2i>(_size)));
	spriteToDisplay.setPosition(_position);
	gameHandler = _gameHandler;
}

void UpdatableSprite::update() {
	gameHandler->getWindowPtr()->draw(spriteToDisplay);
}

bool UpdatableSprite::shouldBeDestroyed() {
	return false;
}