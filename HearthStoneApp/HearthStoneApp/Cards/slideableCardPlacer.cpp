#include "slideableCardPlacer.h"
#include "../myHelper.h"

SlideableCardPlacer::SlideableCardPlacer(sf::Vector2f _restingPosition, sf::Vector2f _size, float _silideAmount,
	std::string _nameOfTexture, MoveType _type, std::shared_ptr<GameHandler> _gameHandler)
	: CardPlacer(_restingPosition, _size, CardPlacerType::SLIDER, _gameHandler) {
	moveType = _type;
	restingPosition = _restingPosition;
	slide = _silideAmount;

	spriteToDisplay = UpdatableSprite(_restingPosition, _size, _nameOfTexture, _gameHandler);

	singleMove = moveType == MoveType::VERTICAL ? sf::Vector2f(0, 1) : sf::Vector2f(1, 0);
	if (_silideAmount < 0) singleMove *= -1.0f;
}

SlideableCardPlacer::SlideableCardPlacer(sf::Vector2f _restingPosition, sf::Vector2f _size, float _silideAmount,
	std::string _nameOfTexture, MoveType _type, std::vector<std::shared_ptr<Card>> _initializePlayersCardVector,
	std::vector<std::shared_ptr<Card>> _initializeOpponentsCardVector, std::shared_ptr<GameHandler> _gameHandler)
	: SlideableCardPlacer(_restingPosition, _size, _silideAmount, _nameOfTexture, _type, _gameHandler) {
	playerCards = _initializePlayersCardVector;
	opponentCards = _initializeOpponentsCardVector;
	for (auto& card : playerCards) {
		card->playerPosesion = true;
		gameHandler->appendCard(card);
	}
	for (auto& card : opponentCards) card->playerPosesion = false;
	_initializePlayersCardVector.insert(_initializePlayersCardVector.end(), _initializeOpponentsCardVector.begin(), _initializeOpponentsCardVector.end());
	cards = _initializePlayersCardVector;
}

void SlideableCardPlacer::move(sf::Vector2f _moveVector) {
	spriteToDisplay.move(_moveVector);
	CardPlacer::move(_moveVector);
	for (auto& card : cards) {
		card->positionBeforeDrag += _moveVector;
	}
}

void SlideableCardPlacer::removeCard(std::shared_ptr<Card> _cardPtr) {
	CardPlacer::removeCard(_cardPtr);
	std::vector<std::shared_ptr<Card>>::iterator it, end;
	if (_cardPtr->playerPosesion) {
		it = playerCards.begin();
		end = playerCards.end();
	}
	else {
		it = opponentCards.begin();
		end = opponentCards.end();
	}
	for (; it != end; ++it) {
		if (*it == _cardPtr) {
			(_cardPtr->playerPosesion ? playerCards : opponentCards).erase(it);
			return;
		}
	}
}

void SlideableCardPlacer::update() {
	CardPlacer::update();
	spriteToDisplay.update();
	if (gameHandler->hasJustFinished) {
		if (gameHandler->getRoundHandlerPtr()->getTurnOrder() == Turn::OPPONENTS_TURN) {
			for (auto& card : opponentCards)
				gameHandler->appendCard(card);
			for (auto& card : playerCards)
				gameHandler->disposeCard(card);
		}
		else {
			for (auto& card : playerCards)
				gameHandler->appendCard(card);
			for (auto& card : opponentCards)
				gameHandler->disposeCard(card);
		}
	}
	if (moveType == MoveType::VERTICAL) {
		if (CardPlacer::isCursorHoverdOver()) {
			if (body.getPosition().y > restingPosition.y + slide) move(singleMove);
		}
		else {
			if (body.getPosition().y < restingPosition.y) move(-singleMove);
		}
	}
}

bool SlideableCardPlacer::shouldBeDestroyed() {
	return false;
}