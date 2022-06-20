#pragma once
#include "updatableSprite.h"

UpdatableSprite::UpdatableSprite() {};

UpdatableSprite::UpdatableSprite(sf::Vector2f _position, sf::Vector2f _size, std::string _textureName, std::shared_ptr<GameHandler> _gameHandler) {
	spriteToDisplay = sf::Sprite(*_gameHandler->getTexturePtrByName(_textureName),
		sf::IntRect(sf::Vector2i(0, 0), static_cast<sf::Vector2i>(_size)));
	spriteToDisplay.setPosition(_position);
	gameHandler = _gameHandler;
}

void UpdatableSprite::update() {
	gameHandler->getWindowPtr()->draw(spriteToDisplay);
}

bool UpdatableSprite::shouldBeDestroyed() {
	return false;
}

void UpdatableSprite::move(sf::Vector2f _moveVector) {
	spriteToDisplay.setPosition(spriteToDisplay.getPosition() + _moveVector);
}