#pragma once
#ifndef BUTTON
#define BUTTON
#include <SFML/Graphics.hpp>
#include "../Handlers/gameHandler.h"
#include "interactive.h"
#include "../buttonBlueprint.h"

//Button class compatible with SFML
class Button : public Interactive {

	//Text used to display text on button
	sf::Text text;

	std::shared_ptr<std::function<void(std::shared_ptr<GameHandler>)>> callBackFunction;

public:

	//Deafult button constructor
	Button(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::string _text,
		std::shared_ptr<sf::Font> _font, sf::Color _fontColor,
		std::shared_ptr<std::function<void(std::shared_ptr<GameHandler>)>> _callBackFunction,
		std::shared_ptr<GameHandler> _gameHandler);

	//Blueprint button constructor
	Button(sf::Vector2f _position, sf::Vector2f _size, ButtonBlueprint _bluePrint,
		std::shared_ptr<GameHandler> _gameHandler);

	//CallBack Function 
	void callback();

	//Function that updates state of object
	void update();
};
#endif