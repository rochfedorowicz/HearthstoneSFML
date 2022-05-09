#pragma once
#include "cardPlacer.h"
#include <thread>
#include <chrono>

std::shared_ptr<CardPlacer> CardPlacer::currentlyActivePlaceHolder = std::shared_ptr<CardPlacer>(nullptr);

CardPlacer::CardPlacer(sf::Vector2f _position, sf::Vector2f _size, bool _belongsToPlayer, std::shared_ptr<GameHandler> _gameHandler)
	: Interactive(_position, _size, sf::Color::Blue, _gameHandler) {
	body = sf::FloatRect(_position, _size);
	playerPosesion = _belongsToPlayer;
}

CardPlacer::CardPlacer(sf::Vector2f _position, sf::Vector2f _size, bool _belongsToPlayer, std::vector<std::shared_ptr<Card>> _initializeCardVector, std::shared_ptr<GameHandler> _gameHandler)
	: CardPlacer(_position, _size, _belongsToPlayer, _gameHandler) {
	cards = _initializeCardVector;
	for (auto& card : cards) card->playerPosesion = _belongsToPlayer;
}

void CardPlacer::addCard(std::shared_ptr<Card> _cardPtr) {
	_cardPtr->texture.setColor(sf::Color(14, 18, 123));
	cards.push_back(_cardPtr);
	_cardPtr->playerPosesion = playerPosesion;
}

bool CardPlacer::shouldBeAligned(std::shared_ptr<Card> _card) {
	enum states {ZERO, ONE, TWO, THREE, FOUR} amount = ZERO;
	for (auto& corner : _card->getCardCorners()) {
		if (body.contains(corner)) amount = static_cast<states>(amount + 1);
	}
	if (amount == FOUR) return false;
	else return true;
}

void CardPlacer::alignCardToBody(std::shared_ptr<Card> _card) {

	auto dist = [](sf::Vector2f _p1, sf::Vector2f _p2) {
		return sqrt(pow(_p1.x - _p2.x, 2) + pow(_p1.y - _p2.y, 2));
	};

	auto getIndexOfMinimum = [](std::vector<double>& _vec) {
		int minIndex = 0;
		for (int i = 1; i < _vec.size(); ++i) {
			if (_vec.at(minIndex) > _vec.at(i)) minIndex = i;
		}
		return minIndex;
	};
	while (shouldBeAligned(_card)) {
		sf::Vector2f centerOfCard = sf::Vector2f(_card->getBounds().left + _card->getBounds().width / 2, _card->getBounds().top + _card->getBounds().height / 2),
			centerOfCH = sf::Vector2f(body.left + body.width / 2, body.top + body.height / 2);

		std::vector<double> distances = { dist(centerOfCard + sf::Vector2f(3,0), centerOfCH), dist(centerOfCard + sf::Vector2f(-3,0), centerOfCH),
			dist(centerOfCard + sf::Vector2f(0,3), centerOfCH), dist(centerOfCard + sf::Vector2f(0,-3), centerOfCH) };
		auto index = getIndexOfMinimum(distances);
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
		std::this_thread::sleep_for(std::chrono::nanoseconds(1500));
		if (CardPlacer::currentlyActivePlaceHolder != shared_from_this()) break;
	}
	_card->setThreadState();
}

void CardPlacer::update() {

	UpdatableRect::update();

	if (Card::getCurrentlyHeldCard().get() == nullptr) {
		currentlyActivePlaceHolder = std::shared_ptr<CardPlacer>(nullptr);
	}

	if (Card::getCurrentlyHeldCard().get() != nullptr && doesCardBelongsToPlacer(Card::getCurrentlyHeldCard())) {
		currentlyActivePlaceHolder = shared_from_this();
	}

	if (Card::getCurrentlyHeldCard().get() != nullptr && isCursorHoverdOver() && gameHandler->isMouseReleased() 
		&& currentlyActivePlaceHolder != shared_from_this()) {

		if (Card::getCurrentlyHeldCard()->playerPosesion == playerPosesion) {
			addCard(Card::getCurrentlyHeldCard());
			currentlyActivePlaceHolder->removeCard(Card::getCurrentlyHeldCard());
		}
		else if (getCardPointedByMouse().get() != nullptr) {
			Card::getCurrentlyHeldCard()->interactWithCard(getCardPointedByMouse());
		}
	}

	for (auto& card : cards) {
		if (!card->isItInThread() && !gameHandler->isMousePressed() && shouldBeAligned(card)) {
			card->setThreadState();
			std::thread th1(&CardPlacer::alignCardToBody, this, card);
			th1.detach();
		}
		for (auto& card2 : cards) {
			if (card != card2 && !card->isItInThread() && !card2->isItInThread() && !gameHandler->isMousePressed() && shouldBeMoved(card, card2)) {
				card->setThreadState();
				card2->setThreadState();
				std::thread th1(&CardPlacer::moveCards, this, card, card2);
				th1.detach();
			}
		}
	}
}

bool CardPlacer::shouldBeMoved(std::shared_ptr<Card> _card, std::shared_ptr<Card> _card2) {
	if (_card->getBounds().intersects(_card2->getBounds())) return true;
	return false;
}

void CardPlacer::moveCards(std::shared_ptr<Card> _card, std::shared_ptr<Card> _card2) {
	auto dist = [](sf::Vector2f _p1, sf::Vector2f _p2) {
		return sqrt(pow(_p1.x - _p2.x, 2) + pow(_p1.y - _p2.y, 2));
	};

	auto getIndexOfMaximum = [](std::vector<double>& _vec) {
		int maxIndex = 0;
		for (int i = 1; i < _vec.size(); ++i) {
			if (_vec.at(maxIndex) < _vec.at(i)) maxIndex = i;
		}
		return maxIndex;
	};
	while (shouldBeMoved(_card, _card2)) {
		sf::Vector2f centerOfCard = sf::Vector2f(_card->getBounds().left + _card->getBounds().width / 2, _card->getBounds().top + _card->getBounds().height / 2),
			centerOfCard2 = sf::Vector2f(_card->getBounds().left + _card->getBounds().width / 2, _card->getBounds().top + _card->getBounds().height / 2);

		std::vector<double> distances = { dist(centerOfCard + sf::Vector2f(1,0), centerOfCard2), dist(centerOfCard + sf::Vector2f(-1,0), centerOfCard2),
				dist(centerOfCard + sf::Vector2f(0,1), centerOfCard2), dist(centerOfCard + sf::Vector2f(0,-1), centerOfCard2) };
		auto index = getIndexOfMaximum(distances);
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
		std::this_thread::sleep_for(std::chrono::nanoseconds(1500));
	}
	_card->setThreadState();
	_card2->setThreadState();
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