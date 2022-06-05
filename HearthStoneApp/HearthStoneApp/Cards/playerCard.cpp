#pragma once
#include "playerCard.h"

PlayerCard::PlayerCard(sf::Vector2f _position, std::shared_ptr<sf::Texture> _texture, std::shared_ptr<PlayerHandler> _playerHandler, std::shared_ptr<GameHandler> _gameHandler)
	: MilitaryCard(_position, _texture, _playerHandler->getDamage(), _playerHandler->getHealth(), _playerHandler->getMaxMana(), _gameHandler) {}

CardType PlayerCard::getCardType() {
	return CardType::PLAYER;
}