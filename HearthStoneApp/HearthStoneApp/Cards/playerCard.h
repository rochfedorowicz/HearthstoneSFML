#pragma once
#ifndef PLAYER_CARD
#define PLAYER_CARD
#include <SFML/Graphics.hpp>
#include "militaryCard.h"
#include "../Handlers/playerHandler.h"

//Class represting player card
class PlayerCard : public MilitaryCard {

public:

	//Main constructor of player card
	PlayerCard(sf::Vector2f _position, std::shared_ptr<sf::Texture> _texture, std::shared_ptr<PlayerHandler> _playerHandler, std::shared_ptr<GameHandler> _gameHandler);

	//Getter for card type
	CardType getCardType();
};
#endif
