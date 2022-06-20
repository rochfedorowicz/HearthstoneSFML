#pragma once
#include "cardPlacer.h"
#include <thread>
#include <chrono>
#include "../myHelper.h"

std::shared_ptr<CardPlacer> CardPlacer::currentlyActivePlaceHolder = std::shared_ptr<CardPlacer>(nullptr);

size_t CardPlacer::numberOfCurrentlyPointedPlaceHolders = 0;

CardPlacer::CardPlacer(sf::Vector2f _position, sf::Vector2f _size, CardPlacerType _type, std::shared_ptr<GameHandler> _gameHandler)
	: Interactive(_position, _size, sf::Color::Transparent, _gameHandler) {
	type = _type;
	isPointedByMouse = false;
}

CardPlacer::CardPlacer(sf::Vector2f _position, sf::Vector2f _size, CardPlacerType _type, std::vector<std::shared_ptr<Card>> _initializeCardVector, std::shared_ptr<GameHandler> _gameHandler)
	: CardPlacer(_position, _size, _type, _gameHandler) {
	cards = _initializeCardVector;
	for (auto& card : cards) {
		card->setPlayerPossesion(type == CardPlacerType::BATTLE_PLACE_PLAYER || _type == CardPlacerType::HERO_PLACE_PLAYER);
		gameHandler->appendCard(card);
	}
}

void CardPlacer::addCard(std::shared_ptr<Card> _cardPtr) {
	cards.push_back(_cardPtr);
	_cardPtr->setPlayerPossesion(type == CardPlacerType::BATTLE_PLACE_PLAYER);
}

bool CardPlacer::shouldBeAligned(std::shared_ptr<Card> _card) {
	int amount = 0;
	for (auto& corner : _card->getCardCorners()) {
		if (body.getGlobalBounds().contains(corner)) ++amount;;
	}
	if (amount >= 4) {
		if (!_card->getDraggability()) _card->changeDraggabilityOfCard();
		return false;
	}
	else {
		if (_card->getDraggability()) _card->changeDraggabilityOfCard();
		return true;
	}
}

//Works as thread!!!
void CardPlacer::alignCardToBody(std::shared_ptr<Card> _card) {	

		sf::Vector2f centerOfCard = _card->getCenterOfBody(), lastPos = _card->getPositionBeforeDrag();

		std::vector<double> distances = { MyHelper::getDistance(centerOfCard + sf::Vector2f(1,0), lastPos),
			MyHelper::getDistance(centerOfCard + sf::Vector2f(-1,0), lastPos),
			MyHelper::getDistance(centerOfCard + sf::Vector2f(0,1), lastPos),
			MyHelper::getDistance(centerOfCard + sf::Vector2f(0,-1), lastPos) };

		int index = MyHelper::getIndexOfSpecifiedItemInVector(distances, [](double& val1, double& val2) {
			return val1 > val2; });
		sf::Vector2f moveVector;
		switch (index)
		{
		case 0: moveVector = sf::Vector2f(1, 0); break;
		case 1: moveVector = sf::Vector2f(-1, 0); break;
		case 2: moveVector = sf::Vector2f(0, 1); break;
		case 3: moveVector = sf::Vector2f(0, -1);
		default: break;
		}
		_card->move(_card->getCardCorners()[0] + moveVector);
		_card->setThreadState();
}


//Works as thread!!!
void CardPlacer::moveCards(std::shared_ptr<Card> _card, std::shared_ptr<Card> _card2) {

	sf::Vector2f centerOfCard = _card->getCenterOfBody(), centerOfCard2 = _card2->getCenterOfBody();

	std::vector<double> distances = { MyHelper::getDistance(centerOfCard + sf::Vector2f(1,0), centerOfCard2),
		MyHelper::getDistance(centerOfCard + sf::Vector2f(-1,0), centerOfCard2),
		MyHelper::getDistance(centerOfCard + sf::Vector2f(0,1), centerOfCard2),
		MyHelper::getDistance(centerOfCard + sf::Vector2f(0,-1), centerOfCard2) };

	auto index = MyHelper::getIndexOfSpecifiedItemInVector(distances, [](double& val1, double& val2) {
		return val1 < val2; });

	sf::Vector2f moveVector;
	switch (index)
	{
	case 0: moveVector = sf::Vector2f(1, 0); break;
	case 1: moveVector = sf::Vector2f(-1, 0); break;
	case 2: moveVector = sf::Vector2f(0, 1); break;
	case 3: moveVector = sf::Vector2f(0, -1);
	default: break;
	}

	_card->move(_card->getCardCorners()[0] + moveVector);
	_card2->move(_card2->getCardCorners()[0] + moveVector * -1.0f);
	_card->setThreadState();
	_card2->setThreadState();
}

void CardPlacer::update() {

	UpdatableRect::update();

	if (isCursorHoverdOver() && !isPointedByMouse) {
		isPointedByMouse = true;
		numberOfCurrentlyPointedPlaceHolders++;
	}
	else if (!isCursorHoverdOver() && isPointedByMouse) {
		isPointedByMouse = false;
		numberOfCurrentlyPointedPlaceHolders--;
	}

	if (Card::getCurrentlyHeldCard().get() == nullptr) {
		currentlyActivePlaceHolder = std::shared_ptr<CardPlacer>(nullptr);
	}

	if (Card::getCurrentlyHeldCard().get() != nullptr && doesCardBelongsToPlacer(Card::getCurrentlyHeldCard())) {
		currentlyActivePlaceHolder = shared_from_this();
	}

	if (Card::getCurrentlyHeldCard().get() != nullptr && isCursorHoverdOver() && gameHandler->isMouseReleased() 
		&& currentlyActivePlaceHolder != shared_from_this()) {
		if ((Card::getCurrentlyHeldCard()->isPossesedByPlayer() && type == CardPlacerType::BATTLE_PLACE_PLAYER &&
				gameHandler->getRoundHandlerPtr()->getTurnOrder() == Turn::PLAYERS_TURN && Card::getCurrentlyHeldCard()->getCardType() != CardType::PLAYER)
				|| (!Card::getCurrentlyHeldCard()->isPossesedByPlayer() && type == CardPlacerType::BATTLE_PLACE_OPPONENT &&
				gameHandler->getRoundHandlerPtr()->getTurnOrder() == Turn::OPPONENTS_TURN && Card::getCurrentlyHeldCard()->getCardType() != CardType::PLAYER)) {
			if (CardPlacer::numberOfCurrentlyPointedPlaceHolders == 1) {
				addCard(Card::getCurrentlyHeldCard());
				currentlyActivePlaceHolder->removeCard(Card::getCurrentlyHeldCard());
			}
		}
		else if (getCardPointedByMouse().get() != nullptr && (((type == CardPlacerType::BATTLE_PLACE_OPPONENT || type == CardPlacerType::HERO_PLACE_OPPONENT) &&
				gameHandler->getRoundHandlerPtr()->getTurnOrder() == Turn::PLAYERS_TURN)
				|| ((type == CardPlacerType::BATTLE_PLACE_PLAYER || type == CardPlacerType::HERO_PLACE_PLAYER) &&
				gameHandler->getRoundHandlerPtr()->getTurnOrder() == Turn::OPPONENTS_TURN))) {
			Card::getCurrentlyHeldCard()->interactWithCard(getCardPointedByMouse());
		}
	}

	for (auto& card : cards) {
		if (!card->isItInThread() && shouldBeAligned(card)) {
			card->setThreadState();
			std::thread aligningThread(&CardPlacer::alignCardToBody, this, card);
			aligningThread.detach();
		}

		for (auto& card2 : cards) {
			if (card != card2 && !card->isItInThread() && !card2->isItInThread() && shouldBeMoved(card, card2)) {
				card->setThreadState();
				card2->setThreadState();
				std::thread movingThread(&CardPlacer::moveCards, this, card, card2);
				movingThread.detach();
			}
		}

		if (card->shouldBeDestroyed()) {
			disposeList.push_back(card);
		}
	}

	for (int i = 0; i < disposeList.size(); ++i) {
		removeCard(disposeList[i]);
	}
	disposeList.clear();
}

bool CardPlacer::shouldBeMoved(std::shared_ptr<Card> _card, std::shared_ptr<Card> _card2) {
	if (_card->getBounds().intersects(_card2->getBounds()) && _card->isPossesedByPlayer() == _card2->isPossesedByPlayer() && !gameHandler->isMousePressed()) return true;
	return false;
}

bool CardPlacer::doesCardBelongsToPlacer(std::shared_ptr<Card> _card) {
	for (auto& card : cards) if (card == _card) return true;	
	return false;
}

void CardPlacer::removeCard(std::shared_ptr<Card> _cardPtr) {
	for (auto it = cards.begin(); it != cards.end(); ++it) {
		if (*it == _cardPtr) {
			cards.erase(it);
			return;
		}
	}
}

std::shared_ptr<Card> CardPlacer::getCardPointedByMouse() {
	for (auto& card : cards)
		if (card->getBounds().contains(gameHandler->getMousePosition())) return card;
	return std::shared_ptr<Card>(nullptr);
}

void CardPlacer::move(sf::Vector2f _moveVector) {
	for (auto& card : cards)
		card->move(card->getCardCorners()[0] + _moveVector);
	body.setPosition(body.getPosition() + _moveVector);
}

bool CardPlacer::shouldBeDestroyed() {
	return false;
}

std::shared_ptr<CardPlacer> CardPlacer::getCurrentlyActivePlaceHolder() {
	return currentlyActivePlaceHolder;
}

size_t CardPlacer::getNumberOfCurrentlyPointedPlaceHolders() {
	return numberOfCurrentlyPointedPlaceHolders;
}