#pragma once
#ifndef CARD_PLACER
#define CARD_PLACER
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "militaryCard.h"

enum class CardPlacerType {BATTLE_PLACE_PLAYER, BATTLE_PLACE_OPPONENT, HERO_PLACE_PLAYER, HERO_PLACE_OPPONENT, SLIDER};

class CardPlacer : public Interactive, public std::enable_shared_from_this<CardPlacer> {

	std::vector<std::shared_ptr<Card>> disposeList;

	bool shouldBeAligned(std::shared_ptr<Card> _card);

	void alignCardToBody(std::shared_ptr<Card> _card);

	void moveCards(std::shared_ptr<Card> _card, std::shared_ptr<Card> _card2);

	bool doesCardBelongsToPlacer(std::shared_ptr<Card> _card);

	CardPlacerType type;

	std::shared_ptr<Card> getCardPointedByMouse();

	bool isPointedByMouse;

protected:

	bool shouldBeMoved(std::shared_ptr<Card> _card, std::shared_ptr<Card> _card2);

	std::vector<std::shared_ptr<Card>> cards;

	virtual void move(sf::Vector2f _moveVector);

	virtual void removeCard(std::shared_ptr<Card> _cardPtr);

	static std::shared_ptr<CardPlacer> currentlyActivePlaceHolder;

	static size_t numberOfCurrentlyPointedPlaceHolders;

public:

	CardPlacer(sf::Vector2f _position, sf::Vector2f _size, CardPlacerType _type, std::shared_ptr<GameHandler> _gameHandler);

	CardPlacer(sf::Vector2f _position, sf::Vector2f _size, CardPlacerType _type, std::vector<std::shared_ptr<Card>> _initializeCardVector, std::shared_ptr<GameHandler> _gameHandler);

	void addCard(std::shared_ptr<Card> _cardPtr);

	void update();

	bool shouldBeDestroyed();

	static std::shared_ptr<CardPlacer> getCurrentlyActivePlaceHolder();

	static size_t getNumberOfCurrentlyPointedPlaceHolders();

};
#endif