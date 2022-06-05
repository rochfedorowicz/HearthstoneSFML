#pragma once
#ifndef CARD
#define CARD
#include <SFML/Graphics.hpp>
#include "../Handlers/gameHandler.h"
#include "../Interactive/interactive.h"

//Enum representing posible card types
enum class CardType {MILITARY, PLAYER, OTHER};

//Class representing card
class Card : public Interactive, public std::enable_shared_from_this<Card> {

	//Texture should be here

	//Logic value indicating if this object should be dragged
	bool shouldBeDragged;

	//Logic value indicating if this object can be dragged
	bool canBeDragged;

	//Lagic value indicating if card is inthread
	bool inThread;

	//Differnce of distance between a grip of mouse and the origin of the card 
	sf::Vector2f differenceOfDrag;

	sf::Vector2f positionBeforeDrag;

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
	virtual void move(sf::Vector2f _change);

	//Getter for isInThread logic value
	bool isItInThread();

	//Setter changing logic state of isInThread value to opposite to current
	void setThreadState();

	//Logic value indicating if this card belongs to player
	bool playerPosesion;

	sf::Vector2f getPositionBeforeDrag();

	bool getDraggability();

	void changeDraggabilityOfCard();

	//Virtual function used for interaction with cards
	virtual void interactWithCard(std::shared_ptr<Card> _card) = 0;

	//Virtual function used for upcasting
	virtual CardType getCardType() = 0;
};
#endif