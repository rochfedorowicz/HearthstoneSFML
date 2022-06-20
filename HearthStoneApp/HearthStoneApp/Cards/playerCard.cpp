#pragma once
#include "playerCard.h"

PlayerCard::PlayerCard(sf::Vector2f _position, std::string _textureName, std::shared_ptr<PlayerHandler> _playerHandler, std::shared_ptr<GameHandler> _gameHandler)
	: MilitaryCard(_position, _gameHandler->getTexturePtrByName(_textureName), _playerHandler->getHealth(), _playerHandler->getDamage(), _playerHandler->getMaxMana(), _gameHandler) {}

CardType PlayerCard::getCardType() {
	return CardType::PLAYER;
}