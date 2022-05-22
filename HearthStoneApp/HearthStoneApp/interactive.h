#pragma once
#ifndef INTERACTIVE
#define INTERACTIVE
#include <SFML/Graphics.hpp>
#include "gameHandler.h"
#include "updateableRect.h"

//Class used to implement checking/interactive functions 
class Interactive : public UpdatableRect{

public:

	//Main constructor
	Interactive(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::shared_ptr<GameHandler> _gameHandler);

	//Logic value idicating if cursos was hovered over the object
	bool isCursorHoverdOver() const;

	//Logic value idicating if interactive object was clicked
	bool isItClicked() const;

	//Overwritten function from abstact updatable class
	virtual void update();

};
#endif