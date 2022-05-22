#pragma once
#ifndef UPDATABLE_RECT
#define UPDATABLE_RECT
#include <SFML/Graphics.hpp>
#include "gameHandler.h"
#include "updatable.h"

class UpdatableRect : public Updatable {
protected:

	//Body of rectangle
	sf::RectangleShape body;

	//Parent game handler
	std::shared_ptr<GameHandler> gameHandler;

public:

	//Main constructor
	UpdatableRect(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::shared_ptr<GameHandler> _gameHandler);

	//Overwritten function from abstact updatable class
	virtual void update();

	//Overwritten function from abstact updatable class
	virtual bool shouldBeDestroyed();

	//Function used for getting center of object's body
	sf::Vector2f getCenterOfBody();

};
#endif