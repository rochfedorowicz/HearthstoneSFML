#pragma once
#ifndef SLIDEABLE_CARD_PLACER
#define SLIDEABLE_CARD_PLACER
#include "cardPlacer.h"
#include "../updatableSprite.h"

/** All posible move types of slideable card placer's moves. */
enum class MoveType {HORZIONTAL, VERTICAL};

/** Class implementing slideable card placers. */
class SlideableCardPlacer : public CardPlacer {

	/** Key position of card placer. */
	sf::Vector2f restingPosition;

	/** Single move value. */
	sf::Vector2f singleMove;

	/** Amount of allowed slide. */
	float slide;

	/** Move's type. */
	MoveType moveType;

	/** Vectors of opponent's and player's cards. */
	std::vector<std::shared_ptr<Card>> playerCards, opponentCards;

	/** Function applying move to card placer. */
	void move(sf::Vector2f _moveVector);

	/** Function removing card from adequate vectors. */
	void removeCard(std::shared_ptr<Card> _cardPtr);

	/** Texture of card placer. */
	UpdatableSprite spriteToDisplay;

	/** Allowed position for new added card. */
	std::vector<std::tuple<sf::Vector2f, bool, bool>> allowedPositions;

	/** Function getting new random card for turn's owner. */
	void giveNewRandomCard(Turn _turn);

	/** Function getting first suitable position from allowed postions for card. */
	sf::Vector2f getFirstSuitablePostion(bool _posesion);

public:

	/** Main slideable card placer's constructor. */
	SlideableCardPlacer(sf::Vector2f _restingPosition, sf::Vector2f _size, float _silideAmount, 
		std::string _nameOfTexture, MoveType _type, std::shared_ptr<GameHandler> _gameHandler);

	/** Slideable card placer's constructor that allows to append initial set of cards for opponent and player. */
	SlideableCardPlacer(sf::Vector2f _restingPosition, sf::Vector2f _size, float _silideAmount,
		std::string _nameOfTexture, MoveType _type, std::vector<std::shared_ptr<Card>> _initializePlayersCardVector,
		std::vector<std::shared_ptr<Card>> _initializeOpponentsCardVector,
		std::shared_ptr<GameHandler> _gameHandler);

	/** Function updating all object's states and maintaining it. */
	void update();

	/** Function indicating if instance of this class should be destroyed. */
	bool shouldBeDestroyed();

};
#endif