#pragma once
#ifndef SLIDEABLE_CARD_PLACER
#define SLIDEABLE_CARD_PLACER
#include "cardPlacer.h"

enum class MoveType {HORZIONTAL, VERTICAL};

class SlideableCardPlacer : public CardPlacer {

	sf::Vector2f restingPosition, singleMove;

	float slide;

	MoveType move;

	std::vector<std::shared_ptr<Card>> playerCards, opponentCards;

	void removeCard(std::shared_ptr<Card> _cardPtr);

public:

	SlideableCardPlacer(sf::Vector2f _restingPosition, sf::Vector2f _size, float _silideAmount,
		MoveType _type, std::shared_ptr<GameHandler> _gameHandler);

	SlideableCardPlacer(sf::Vector2f _restingPosition, sf::Vector2f _size, float _silideAmount,
		MoveType _type, std::vector<std::shared_ptr<Card>> _initializePlayersCardVector,
		std::vector<std::shared_ptr<Card>> _initializeOpponentsCardVector,
		std::shared_ptr<GameHandler> _gameHandler);

	void update();

};
#endif