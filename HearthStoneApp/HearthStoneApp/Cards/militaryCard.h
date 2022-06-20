#pragma once
#ifndef MILITARY_CARD
#define MILITARY_CARD
#include "card.h"
#include "../updateableText.h"

//Class representing military card
class MilitaryCard : public Card {
	
	//Lables used to display card statistics
	UpdatableText damageLabel, healthLabel;

protected:

	//Amount of health and damage dealed military card possesses
	int health, damage, mana;

public:

	//Deafult military card constructor
	MilitaryCard(sf::Vector2f _position, std::shared_ptr<sf::Texture> _texture, int _health, int _damage, int _mana, std::shared_ptr<GameHandler> _gameHandler);

	//Deafult military card constructor
	MilitaryCard(sf::Vector2f _position,  std::shared_ptr<GameHandler> _gameHandler);

	//Interacting with another cards
	void interactWithCard(std::shared_ptr<Card> _card);

	//Virtual function that updates state of object
	void update();

	//Card type getter
	virtual CardType getCardType();

	//Logic value indicating if card should be disposed
	bool shouldBeDestroyed();

	//Function moving object (generally update its poistion)
	void move(sf::Vector2f _change);
};
#endif