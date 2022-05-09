#pragma once
#ifndef CARD
#define CARD
#include <SFML/Graphics.hpp>
#include "gameHandler.h"
#include "interactive.h"

//Class representing card
class Card : public Interactive, public std::enable_shared_from_this<Card> {

	//Texture should be here

	//Logic value indicating if this object should be dragged
	bool shouldBeDragged;

	bool inThread;

	//Differnce of distance between a grip of mouse and the origin of the card 
	sf::Vector2f differenceOfDrag;

	static std::shared_ptr<Card> currentlyHeldCard;

public:
		
	//Texture of a card
	sf::Sprite texture;

	//Deafult card constructor
	Card(sf::Vector2f _position, std::shared_ptr<sf::Texture> _texture, std::shared_ptr<GameHandler> _gameHandler);

	//Virtual function that updates state of object
	void update();

	//Getter for card corners as a vector
	std::vector<sf::Vector2f> getCardCorners();

	//Getter for card body
	sf::FloatRect getBounds();

	//Getter for currently held card
	static std::shared_ptr<Card> getCurrentlyHeldCard();


	//Function moving object (generally update its poistion)
	void move(sf::Vector2f _change);

	bool isItInThread();

	void setThreadState();

	bool playerPosesion;

	virtual void interactWithCard(std::shared_ptr<Card> _card) = 0;
};
#endif