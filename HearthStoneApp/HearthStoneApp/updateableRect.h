#pragma once
#ifndef UPDATABLE_RECT
#define UPDATABLE_RECT
#include <SFML/Graphics.hpp>
#include "gameHandler.h"
#include "updatable.h"

class UpdatableRect : public Updatable {
protected:

	sf::RectangleShape body;

	std::shared_ptr<GameHandler> gameHandler;

public:

	UpdatableRect(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::shared_ptr<GameHandler> _gameHandler);

	//Overwritten function from abstact updatable class
	virtual void update();

	virtual bool shouldBeDestroyed();

	sf::Vector2f getCenterOfBody();

};
#endif