#pragma once
#include "militaryCard.h"
#include "../myHelper.h"
#define UP_CAST(upperClass, object) dynamic_cast<upperClass*>(object.get())

MilitaryCard::MilitaryCard(sf::Vector2f _position, std::shared_ptr<sf::Texture> _texture, int _health, int _damage, int _mana, std::shared_ptr<GameHandler> _gameHandler)
	: Card(_position, _texture, _gameHandler) {
	health = _health;
	damage = _damage;
	mana = _mana;
	damageLabel = UpdatabText(_position + sf::Vector2f(0.2 * body.getSize().x, 0.85 * body.getSize().y), 0.25 * body.getSize().y, MyHelper::convertIntToString(damage), gameHandler->getFontPtrByName("Calibri"), sf::Color::Black, _gameHandler);
	healthLabel = UpdatabText(_position + sf::Vector2f(0.8 * body.getSize().x, 0.85 * body.getSize().y), 0.25 * body.getSize().y, MyHelper::convertIntToString(health), gameHandler->getFontPtrByName("Calibri"), sf::Color::Black, _gameHandler);
}

void MilitaryCard::interactWithCard(std::shared_ptr<Card> _card) {
	if ((_card->getCardType() == CardType::MILITARY || _card->getCardType() == CardType::PLAYER) && gameHandler->getPlayerPtr()->consumeMana(mana)) {
		auto militaryCard2 = UP_CAST(MilitaryCard, _card);
		militaryCard2->health -= damage;
	}
}

void MilitaryCard::update() {
	Card::update();
	damageLabel.contentUpdate(MyHelper::convertIntToString(damage));
	healthLabel.contentUpdate(MyHelper::convertIntToString(health));
	damageLabel.update();
	healthLabel.update();
	move(body.getPosition());
}

CardType MilitaryCard::getCardType() {
	return CardType::MILITARY;
}

bool MilitaryCard::shouldBeDestroyed() {
	return health <= 0;
}

void MilitaryCard::move(sf::Vector2f _change) {
	Card::move(_change);
	damageLabel.positionUpdate(_change + sf::Vector2f(0.2 * body.getSize().x, 0.85 * body.getSize().y));
	healthLabel.positionUpdate(_change + sf::Vector2f(0.8 * body.getSize().x, 0.85 * body.getSize().y));
}