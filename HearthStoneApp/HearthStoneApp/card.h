#pragma once
#ifndef CARD
#define CARD
#include <SFML/Graphics.hpp>
#include "gameHandler.h"
#include "interactive.h"

//Class representing card
class Card : public Interactive {

	//Texture of a card
	sf::Sprite texture;

	//Logic value indicating if this object should be dragged
	bool shouldBeDragged;

	//Differnce of distance between a grip of mouse and the origin of the card 
	sf::Vector2f differenceOfDrag;

	//Function moving object (generally update its poistion)
	void move(sf::Vector2f _change);

public:
		
	//Deafult card constructor
	Card(std::shared_ptr<sf::Texture>  _texture, std::shared_ptr<GameHandler> _gameHandler);

	//Virtual function that updates state of object
	void update();
};
#endif