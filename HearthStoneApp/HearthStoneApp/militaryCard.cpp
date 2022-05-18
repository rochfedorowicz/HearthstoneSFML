#pragma once
#include "militaryCard.h"
#include <sstream>
#define UP_CAST(upperClass, object) dynamic_cast<upperClass*>(object.get())

MilitaryCard::MilitaryCard(sf::Vector2f _position, std::shared_ptr<sf::Texture> _texture, int _health, int _damage, std::shared_ptr<GameHandler> _gameHandler)
	: Card(_position, _texture, _gameHandler) {
	health = _health;
	damage = _damage;
}

void MilitaryCard::interactWithCard(std::shared_ptr<Card> _card) {
	if (_card->getCardType() == CardType::MILITARY) {
		auto militaryCard2 = UP_CAST(MilitaryCard, _card);
		militaryCard2->health -= damage;
	}
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

CardType MilitaryCard::getCardType() {
	return CardType::MILITARY;
}

bool MilitaryCard::shouldBeDestroyed() {
	return health <= 0;
}