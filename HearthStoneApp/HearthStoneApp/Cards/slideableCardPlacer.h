#pragma once
#ifndef SLIDEABLE_CARD_PLACER
#define SLIDEABLE_CARD_PLACER
#include "cardPlacer.h"
#include "../updatableSprite.h"

enum class MoveType {HORZIONTAL, VERTICAL};

class SlideableCardPlacer : public CardPlacer {

	sf::Vector2f restingPosition, singleMove;

	float slide;

	MoveType moveType;

	std::vector<std::shared_ptr<Card>> playerCards, opponentCards;

	void move(sf::Vector2f _moveVector);

	void removeCard(std::shared_ptr<Card> _cardPtr);

	UpdatableSprite spriteToDisplay;

	std::vector<std::tuple<sf::Vector2f, bool, bool>> allowedPositions;

	void giveNewRandomCard(Turn _turn);

	sf::Vector2f getFirstSuitablePostion(bool _posesion);

public:

	SlideableCardPlacer(sf::Vector2f _restingPosition, sf::Vector2f _size, float _silideAmount, 
		std::string _nameOfTexture, MoveType _type, std::shared_ptr<GameHandler> _gameHandler);

	SlideableCardPlacer(sf::Vector2f _restingPosition, sf::Vector2f _size, float _silideAmount,
		std::string _nameOfTexture, MoveType _type, std::vector<std::shared_ptr<Card>> _initializePlayersCardVector,
		std::vector<std::shared_ptr<Card>> _initializeOpponentsCardVector,
		std::shared_ptr<GameHandler> _gameHandler);

	void update();

	bool shouldBeDestroyed();

};
#endif