#pragma once
#ifndef MILITARY_CARD
#define MILITARY_CARD
#include "card.h"

//Class representing military card
class MilitaryCard : public Card {

	//Amount of health military card possesses
	int health;
	
	//Amount of damage military card can deal
	int damage;

	sf::Text info;

public:

	//Deafult military card constructor
	MilitaryCard(sf::Vector2f _position, std::shared_ptr<sf::Texture> _texture, int _health, int _damage, std::shared_ptr<GameHandler> _gameHandler);

	//Interacting with another cards
	virtual void interactWithCard(std::shared_ptr<Card> _card);

	//Virtual function that updates state of object
	void update();
};
#endif