#pragma once
#ifndef CARD
#define CARD
#include <SFML/Graphics.hpp>
#include "gameHandler.h"
#include "interactive.h"

class Card : public Interactive {

	sf::Sprite texture;

	bool shouldBeDragged;

	sf::Vector2f differenceOfDrag;

	//Overwritten function from abstact drawable class
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
		
	Card(std::shared_ptr<sf::Texture>  _texture, std::shared_ptr<GameHandler> _gameHandler);

	void move(sf::Vector2f _change);

	//Virtual function that updates state of object
	void update();
};
#endif