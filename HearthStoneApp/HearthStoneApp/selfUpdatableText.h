#pragma once
#ifndef SELF_UPDATABLE_TEXT
#define SELF_UPDATABLE_TEXT
#include "updateableText.h"
#include <functional>

/** Class representing self updatable texts. */
class SelfUpdatableText : public UpdatableText {

	/** Pointer to function allowing class to self-update. */
	std::shared_ptr<std::function<std::string(std::shared_ptr<GameHandler>)>> getValueFunction;

public:

	/** Main constructor. */
	SelfUpdatableText(sf::Vector2f _position, sf::Vector2f _size, std::shared_ptr<sf::Font> _font,
		sf::Color _fontColor, std::shared_ptr<std::function<std::string(std::shared_ptr<GameHandler>)>> _getValueFunction,
		std::shared_ptr<GameHandler> _gameHandler);

	/** Overwritten function from abstact updatable class */
	void update();

	/** Overwritten function from abstact updatable class */
	bool shouldBeDestroyed();
};
#endif