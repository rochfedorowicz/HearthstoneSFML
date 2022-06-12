#pragma once
#ifndef SELF_UPDATABLE_TEXT
#define SELF_UPDATABLE_TEXT
#include "updateableText.h"
#include <functional>

class SelfUpdatableText : public UpdatableText {

	std::shared_ptr<std::function<std::string(std::shared_ptr<GameHandler>)>> getValueFunction;

public:

	SelfUpdatableText(sf::Vector2f _position, sf::Vector2f _size, std::string _text, std::shared_ptr<sf::Font> _font,
		sf::Color _fontColor, std::shared_ptr<std::function<std::string(std::shared_ptr<GameHandler>)>> _getValueFunction,
		std::shared_ptr<GameHandler> _gameHandler);

	//Overwritten function from abstact updatable class
	void update();

	bool shouldBeDestroyed();
};
#endif