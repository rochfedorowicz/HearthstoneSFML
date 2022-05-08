#pragma once
#include "card.h"

std::shared_ptr<Card> Card::currentlyHeldCard = std::shared_ptr<Card>(nullptr);

void Card::update() {
	Interactive::update();
	gameHandler->getWindowPtr()->draw(texture);
	if (isItClicked()) {
		Card::currentlyHeldCard = shared_from_this();
		shouldBeDragged = true;
		differenceOfDrag = gameHandler->getMousePosition() - body.getPosition();
	}
	if (shouldBeDragged) {
		if (gameHandler->isMousePressed())
			move(gameHandler->getMousePosition() - differenceOfDrag);
		else {
			shouldBeDragged = false;
			Card::currentlyHeldCard = std::shared_ptr<Card>(nullptr);
		}
	}
}

Card::Card(sf::Vector2f _position, std::shared_ptr<sf::Texture> _texture, std::shared_ptr<GameHandler> _gameHandler) 
	: Interactive(_position, sf::Vector2f(_texture->getSize()), sf::Color(0, 0, 0), _gameHandler) {
	texture = sf::Sprite(*_texture);
	texture.setPosition(_position);
	shouldBeDragged = inThread = false;
}

void Card::move(sf::Vector2f _change) {
	body.setPosition(_change);
	texture.setPosition(_change);
	
}

std::vector<sf::Vector2f> Card::getCardCorners() {
	return { body.getPosition(), sf::Vector2f(body.getPosition().x + body.getSize().x, body.getPosition().y),
		sf::Vector2f(body.getPosition().x, body.getPosition().y + body.getSize().y), body.getPosition() + body.getSize()};
}

sf::FloatRect Card::getBounds() {
	return body.getGlobalBounds();
}

std::shared_ptr<Card> Card::getCurrentlyHeldCard() {
	return currentlyHeldCard;
}

bool Card::isItInThread() {
	return inThread;
}

void Card::setThreadState() {
	inThread = inThread == true ? false : true;
}