#pragma once
#ifndef BUTTON
#define BUTTON
#include <SFML/Graphics.hpp>
#include "gameHandler.h"
#include "interactive.h"
#include "callbacks.h"

//Button class compatible with SFML
class Button : public Interactive {

	//Text used to display text on button
	sf::Text text;

	//Enum showing wich function should be invoke after clicking this button
	CallbacksEnum callBackFunction;

	//Overwritten function from abstact drawable class
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	//Deafult button constructor
	Button(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::string _text,
		std::shared_ptr<sf::Font> _font, sf::Color _fontColor, CallbacksEnum _callBackFunction,
		std::shared_ptr<GameHandler> _gameHandler);

	//CallBack Function 
	void callback() const;

	//Function that updates state of object
	void update();
};
#endif