#pragma once
#include "militaryCard.h"
#include <sstream>

MilitaryCard::MilitaryCard(sf::Vector2f _position, std::shared_ptr<sf::Texture> _texture, int _health, int _damage, std::shared_ptr<GameHandler> _gameHandler)
	: Card(_position, _texture, _gameHandler) {
	health = _health;
	damage = _damage;
}

void MilitaryCard::interactWithCard(std::shared_ptr<Card> _card) {
	MilitaryCard& militaryCard2 = dynamic_cast<MilitaryCard&>(*_card.get());
	militaryCard2.health -= damage;
}

void MilitaryCard::update() {
	Card::update();
	std::stringstream s;
	s << health << "         " << damage;
	std::string s2 = "";
	std::getline(s, s2);
	info = sf::Text(s2, *gameHandler->getFontPtrByName("Calibri"));
	info.setPosition(body.getPosition());
	info.setFillColor(sf::Color(255, 0, 0));
	info.setOutlineThickness(2);
	gameHandler->getWindowPtr()->draw(info);
}