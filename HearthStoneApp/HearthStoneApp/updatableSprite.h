#pragma once
#pragma once
#ifndef UPDATABLE_SPRITE
#define UPDATABLE_SPRITE
#include "Handlers/gameHandler.h"
#include "Interfaces/updatable.h"

class UpdatableSprite: public Updatable {
protected:

	//Sprite do be displayed 
	sf::Sprite spriteToDisplay;

	//Parent game handler
	std::shared_ptr<GameHandler> gameHandler;

public:

	//Main constructor
	UpdatableSprite(sf::Vector2f _position, sf::Vector2f _size, std::string _textureName, std::shared_ptr<GameHandler> _gameHandler);

	//Overwritten function from abstact updatable class
	virtual void update();

	//Overwritten function from abstact updatable class
	virtual bool shouldBeDestroyed();
};
#endif