#pragma once
#ifndef BUTTON
#define BUTTON
#include <SFML/Graphics.hpp>
#include "gameHandler.h"
#include "interactive.h"
#include "callbacks.h"
#include "buttonBlueprint.h"

//Button class compatible with SFML
class Button : public Interactive {

	//Text used to display text on button
	sf::Text text;

	//Enum showing wich function should be invoke after clicking this button
	CallbacksEnum callBackFunction;

public:

	//Deafult button constructor
	Button(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::string _text,
		std::shared_ptr<sf::Font> _font, sf::Color _fontColor, CallbacksEnum _callBackFunction,
		std::shared_ptr<GameHandler> _gameHandler);

	//Blueprint button constructor
	Button(sf::Vector2f _position, sf::Vector2f _size, ButtonBlueprint _bluePrint, std::string _text,
		CallbacksEnum _callBackFunction, std::shared_ptr<GameHandler> _gameHandler);

	//CallBack Function 
	void callback() const;

	//Function that updates state of object
	void update();
};
#endif