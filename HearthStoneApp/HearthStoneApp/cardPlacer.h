#pragma once
#ifndef CARD_PLACER
#define CARD_PLACER
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "militaryCard.h"

enum class CardPlacerType {BATTLE_PLACE_PLAYER, BATTLE_PLACE_OPPONENT, HERO_PLACE_PLAYER, HERO_PLACE_OPPONENT};

class CardPlacer : public Interactive, public std::enable_shared_from_this<CardPlacer> {
	
	sf::FloatRect body;

	std::vector<std::shared_ptr<Card>> cards, disposeList;

	void update();

	bool shouldBeAligned(std::shared_ptr<Card> _card);

	void alignCardToBody(std::shared_ptr<Card> _card);

	bool shouldBeMoved(std::shared_ptr<Card> _card, std::shared_ptr<Card> _card2);

	void moveCards(std::shared_ptr<Card> _card, std::shared_ptr<Card> _card2);

	bool doesCardBelongsToPlacer(std::shared_ptr<Card> _card);

	void removeCard(std::shared_ptr<Card> _cardPtr);

	CardPlacerType type;

	std::shared_ptr<Card> getCardPointedByMouse();

public:

	CardPlacer(sf::Vector2f _position, sf::Vector2f _size, CardPlacerType _type, std::shared_ptr<GameHandler> _gameHandler);

	CardPlacer(sf::Vector2f _position, sf::Vector2f _size, CardPlacerType _type, std::vector<std::shared_ptr<Card>> _initializeCardVector, std::shared_ptr<GameHandler> _gameHandler);

	void addCard(std::shared_ptr<Card> _cardPtr);

	static std::shared_ptr<CardPlacer> currentlyActivePlaceHolder;

};
#endif