#pragma once
#ifndef UPDATABLE_TEXT
#define UPDATABLE_TEXT
#include <SFML/Graphics.hpp>
#include "Handlers/gameHandler.h"
#include "Interfaces/updatable.h"

class UpdatableText: public Updatable {

	//Text do be displayed 
	sf::Text textToDisplay;

protected:
	//Parent game handler
	std::shared_ptr<GameHandler> gameHandler;

public:

	UpdatableText();

	UpdatableText(sf::Vector2f _position, sf::Vector2f _size, std::string _text, std::shared_ptr<sf::Font> _font,
		sf::Color _fontColor, std::shared_ptr<GameHandler> _gameHandler);

	UpdatableText(sf::Vector2f _position, sf::Vector2f _size, std::string _text, std::shared_ptr<sf::Font> _font,
		sf::Color _fontColor, float _angle, std::shared_ptr<GameHandler> _gameHandler);

	UpdatableText(sf::Vector2f _position, float _size, std::string _text, std::shared_ptr<sf::Font> _font,
		sf::Color _fontColor, std::shared_ptr<GameHandler> _gameHandler);

	//Overwritten function from abstact updatable class
	void update();

	bool shouldBeDestroyed();

	void contentUpdate(std::string _newContent);

	void positionUpdate(sf::Vector2f _change);

};
#endif