#pragma once
#ifndef CARD_PLACER
#define CARD_PLACER
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "militaryCard.h"

/** Enum showing all posible card placer types. */
enum class CardPlacerType {BATTLE_PLACE_PLAYER, BATTLE_PLACE_OPPONENT, HERO_PLACE_PLAYER, HERO_PLACE_OPPONENT, SLIDER};

/** Class representing card placer. */
class CardPlacer : public Interactive, public std::enable_shared_from_this<CardPlacer> {

	/** List of cards that are to be deleted from the cards list of
	* this particular card placer at the end of the updating loop. */
	std::vector<std::shared_ptr<Card>> disposeList;

	/** Logic value indicating if card should be aligned to card placer body. */
	bool shouldBeAligned(std::shared_ptr<Card> _card);

	/** Function aligning card to card placer's body. Works in thread. */
	void alignCardToBody(std::shared_ptr<Card> _card);

	/** Function moving cards apart. Works in thread. */
	void moveCards(std::shared_ptr<Card> _card, std::shared_ptr<Card> _card2);

	/** Logic value checking if particular card belong to placer. */
	bool doesCardBelongsToPlacer(std::shared_ptr<Card> _card);

	/** Stores card placer's type. */
	CardPlacerType type;

	/** Function getting back card that is pointed by mouse and belongs to this card placer. */
	std::shared_ptr<Card> getCardPointedByMouse();

	/** Logic value indicating if card placer is pointed by mouse. */
	bool isPointedByMouse;

protected:

	/** Logic value indicating if two cards should be moved apart. */
	bool shouldBeMoved(std::shared_ptr<Card> _card, std::shared_ptr<Card> _card2);

	/** Vetors of cards that belongs to card placer. */
	std::vector<std::shared_ptr<Card>> cards;

	/** Function moving card placer and cards. */
	virtual void move(sf::Vector2f _moveVector);

	/** Function removing card from card's vector. */
	virtual void removeCard(std::shared_ptr<Card> _cardPtr);

	/** Function getting pointer to currently active place holder. */
	static std::shared_ptr<CardPlacer> currentlyActivePlaceHolder;

	/** Currenlty pointed place holder's number. */
	static size_t numberOfCurrentlyPointedPlaceHolders;

public:

	/** Main card placer's constructor. */
	CardPlacer(sf::Vector2f _position, sf::Vector2f _size, CardPlacerType _type, std::shared_ptr<GameHandler> _gameHandler);

	/** Card placer's constructor that allows to append initial set of cards. */
	CardPlacer(sf::Vector2f _position, sf::Vector2f _size, CardPlacerType _type, std::vector<std::shared_ptr<Card>> _initializeCardVector, std::shared_ptr<GameHandler> _gameHandler);

	/** Function adding card to card's vector. */
	void addCard(std::shared_ptr<Card> _cardPtr);

	/** Function updating all object's states and maintaining it. */
	void update();

	/** Function indicating if instance of this class should be destroyed. */
	bool shouldBeDestroyed();

	/** Getter for currently active place holder. */
	static std::shared_ptr<CardPlacer> getCurrentlyActivePlaceHolder();

	/* Getter for currently active place holder's number. */
	static size_t getNumberOfCurrentlyPointedPlaceHolders();

};
#endif