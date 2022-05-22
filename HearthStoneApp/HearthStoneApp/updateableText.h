#pragma once
#ifndef UPDATABLE_TEXT
#define UPDATABLE_TEXT
#include <SFML/Graphics.hpp>
#include "gameHandler.h"
#include "updatable.h"

class UpdatabText: public Updatable {

	//Text do be displayed 
	sf::Text textToDisplay;

	//Parent game handler
	std::shared_ptr<GameHandler> gameHandler;

public:

	UpdatabText();

	UpdatabText(sf::Vector2f _position, sf::Vector2f _size, std::string _text, std::shared_ptr<sf::Font> _font,
		sf::Color _fontColor, std::shared_ptr<GameHandler> _gameHandler);

	//Overwritten function from abstact updatable class
	void update();

	bool shouldBeDestroyed();

	void contentUpdate(std::string _newContent);

	void positionUpdate(sf::Vector2f _change);

};
#endif