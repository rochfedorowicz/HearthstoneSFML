#pragma once
#ifndef INTERACTIVE
#define INTERACTIVE
#include <SFML/Graphics.hpp>
#include "updatable.h"
#include "gameHandler.h"

class Interactive : public Updatable{

protected:

	sf::RectangleShape body;

	std::shared_ptr<GameHandler> gameHandler;

	//Overwritten function from abstact drawable class
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	Interactive(sf::Vector2f _position, sf::Vector2f _size, std::shared_ptr<GameHandler> _gameHandler);

	bool isCursorHoverdOver() const;

	bool isItClicked() const;

	//Overwritten function from abstact updatable class
	virtual void update() = 0;

};
#endif