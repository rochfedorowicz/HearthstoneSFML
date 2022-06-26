#pragma once
#pragma once
#ifndef UPDATABLE_SPRITE
#define UPDATABLE_SPRITE
#include "Handlers/gameHandler.h"
#include "Interfaces/updatable.h"

/** Class being adaptation of sprites from SFML that can work with game handler properly. */
class UpdatableSprite: public Updatable {
protected:

	/** Sprite do be displayed. */
	sf::Sprite spriteToDisplay;

	/** Parent game handler. */
	std::shared_ptr<GameHandler> gameHandler;

public:

	/** Default constructor. */
	UpdatableSprite();

	/** Main constructor. */
	UpdatableSprite(sf::Vector2f _position, sf::Vector2f _size, std::string _textureName, std::shared_ptr<GameHandler> _gameHandler);

	/** Overwritten function from abstact updatable class. */
	virtual void update();

	/** Overwritten function from abstact updatable class. */
	virtual bool shouldBeDestroyed();

	/** Function moving object. */
	void move(sf::Vector2f _moveVector);
};
#endif