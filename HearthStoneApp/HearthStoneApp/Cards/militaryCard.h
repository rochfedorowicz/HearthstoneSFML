#pragma once
#ifndef MILITARY_CARD
#define MILITARY_CARD
#include "card.h"
#include "../updateableText.h"
#include "../cardBlueprint.h"

/** Class representing military card. */
class MilitaryCard : public Card {
	
	/** Lables used to display card statistics. */
	UpdatableText damageLabel, healthLabel, manaLabel;

protected:

	/** Amount of health military card possesses. */
	int health;

	/** Amount of damage dealed military card possesses. */
	int damage;

	/** Amount of mana military card possesses. */
	int mana;

public:

	/** Main military card's constructor. */
	MilitaryCard(sf::Vector2f _position, std::shared_ptr<sf::Texture> _texture, int _health, int _damage, int _mana, std::shared_ptr<GameHandler> _gameHandler);

	/** Military card's constructor that uses predefined set of parameters called blueprint. */
	MilitaryCard(sf::Vector2f _position, CardBlueprint _cardBlueprint, std::shared_ptr<GameHandler> _gameHandler);

	/** Interacting with another cards. */
	void interactWithCard(std::shared_ptr<Card> _card);

	/** Updates state of object. */
	void update();

	/** Card type getter. */
	virtual CardType getCardType();

	/** Logic value indicating if card should be disposed. */
	bool shouldBeDestroyed();

	/** Function moving object(generally update its poistion). */
	void move(sf::Vector2f _change);
};
#endif