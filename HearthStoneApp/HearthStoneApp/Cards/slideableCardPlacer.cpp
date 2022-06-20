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

	auto move = sf::Vector2f(body.getGlobalBounds().width / 5.0, 0);
	auto firstPosition = body.getPosition() + sf::Vector2f(20, 20);
	allowedPositions = { {firstPosition, 1, 1 }, {firstPosition + 1.0f * move, 1, 1},
		{firstPosition + 2.0f * move, 1, 1}, {firstPosition + 3.0f * move, 1, 1},
		{firstPosition + 4.0f * move, 1, 1}};
}

SlideableCardPlacer::SlideableCardPlacer(sf::Vector2f _restingPosition, sf::Vector2f _size, float _silideAmount,
	std::string _nameOfTexture, MoveType _type, std::vector<std::shared_ptr<Card>> _initializePlayersCardVector,
	std::vector<std::shared_ptr<Card>> _initializeOpponentsCardVector, std::shared_ptr<GameHandler> _gameHandler)
	: SlideableCardPlacer(_restingPosition, _size, _silideAmount, _nameOfTexture, _type, _gameHandler) {
	playerCards = _initializePlayersCardVector;
	opponentCards = _initializeOpponentsCardVector;
	for (auto& card : playerCards) {
		card->setPlayerPossesion(true);
		card->move(getFirstSuitablePostion(true));
		gameHandler->appendCard(card);
	}
	for (auto& card : opponentCards) {
		card->setPlayerPossesion(false);
		card->move(getFirstSuitablePostion(false));
	}
	_initializePlayersCardVector.insert(_initializePlayersCardVector.end(), _initializeOpponentsCardVector.begin(), _initializeOpponentsCardVector.end());
	cards = _initializePlayersCardVector;
}

void SlideableCardPlacer::move(sf::Vector2f _moveVector) {
	spriteToDisplay.move(_moveVector);
	CardPlacer::move(_moveVector);
	for (auto& card : cards) {
		card->setPositionBeforeDrag(card->getPositionBeforeDrag()  + _moveVector);
	}
}

void SlideableCardPlacer::removeCard(std::shared_ptr<Card> _cardPtr) {
	CardPlacer::removeCard(_cardPtr);
	std::vector<std::shared_ptr<Card>>::iterator it, end;
	if (_cardPtr->isPossesedByPlayer()) {
		it = playerCards.begin();
		end = playerCards.end();
	}
	else {
		it = opponentCards.begin();
		end = opponentCards.end();
	}
	for (; it != end; ++it) {
		if (*it == _cardPtr) {
			(_cardPtr->isPossesedByPlayer() ? playerCards : opponentCards).erase(it);
			return;
		}
	}
}

void SlideableCardPlacer::update() {
	CardPlacer::update();
	spriteToDisplay.update();
	if (gameHandler->hasRoundJustFinished()) {
		if (gameHandler->getRoundHandlerPtr()->getTurnOrder() == Turn::OPPONENTS_TURN) {
			for (auto& card : playerCards)
				gameHandler->disposeCard(card);
			if (opponentCards.size() < 3) giveNewRandomCard(Turn::OPPONENTS_TURN);
			for (auto& card : opponentCards)
				gameHandler->appendCard(card);

		}
		else {
			for (auto& card : opponentCards)
				gameHandler->disposeCard(card);
			if (playerCards.size() < 3) giveNewRandomCard(Turn::PLAYERS_TURN);
			for (auto& card : playerCards)
				gameHandler->appendCard(card);

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

void SlideableCardPlacer::giveNewRandomCard(Turn _turn) {
	std::vector<CardBlueprint> blueprints = {cardBlueprints::ORC, cardBlueprints::WARRIOR, cardBlueprints::WIKING};
	int blueprintNumber = MyHelper::getRandomInt(0, 2);
	std::shared_ptr<Card> newCard = std::make_shared<MilitaryCard>(body.getPosition() + sf::Vector2f(10, 10), blueprints.at(blueprintNumber), gameHandler);
	newCard->setPlayerPossesion(_turn == Turn::PLAYERS_TURN ? true : false);
	newCard->move(getFirstSuitablePostion(_turn == Turn::PLAYERS_TURN ? true : false));
	cards.push_back(newCard);
	(_turn == Turn::PLAYERS_TURN ? playerCards : opponentCards).push_back(newCard);
}


sf::Vector2f SlideableCardPlacer::getFirstSuitablePostion(bool _posesion) {
	if (_posesion) {
		for (auto& position : allowedPositions)
			if (std::get<1>(position)) {
				std::get<1>(position) = false;
				return std::get<0>(position);
			}
	}
	else {
		for (auto& position : allowedPositions)
			if (std::get<2>(position)) {
				std::get<2>(position) = false;
				return std::get<0>(position);
			}
	}
	return sf::Vector2f(-1000, -1000);
}

