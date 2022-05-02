#pragma once
#ifndef INTERACTIVE
#define INTERACTIVE
#include <SFML/Graphics.hpp>
#include "gameHandler.h"
#include "updatable.h"

class Interactive : public Updatable{
protected:

	sf::RectangleShape body;

	std::shared_ptr<GameHandler> gameHandler;

public:

	Interactive(sf::Vector2f _position, sf::Vector2f _size, std::shared_ptr<GameHandler> _gameHandler);

	bool isCursorHoverdOver() const;

	bool isItClicked() const;

	//Overwritten function from abstact updatable class
	virtual void update();

};
#endif