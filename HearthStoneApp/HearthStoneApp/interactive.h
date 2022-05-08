#pragma once
#ifndef INTERACTIVE
#define INTERACTIVE
#include <SFML/Graphics.hpp>
#include "gameHandler.h"
#include "updateableRect.h"

class Interactive : public UpdatableRect{

public:

	Interactive(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::shared_ptr<GameHandler> _gameHandler);

	bool isCursorHoverdOver() const;

	bool isItClicked() const;

	//Overwritten function from abstact updatable class
	virtual void update();

};
#endif