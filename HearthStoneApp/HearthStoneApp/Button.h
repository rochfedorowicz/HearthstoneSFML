#pragma once
#include <SFML/Graphics.hpp>
#include "gameHandler.h"

typedef void (*function)(std::shared_ptr<GameHandler>);

//Button class compatible with SFML
class Button : public sf::Drawable {
	
private:

	//Rectangle used to display button body
	sf::RectangleShape body;

	//Text used to display text on button
	sf::Text text;

	//Pointer to callback function
	function callBackFunction;

	//Pointer to game handler (allows to manage callbacks and drawing function)
	std::shared_ptr<GameHandler> gameHandler;

	//Overwritten function from abstact drawable class
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	//Deafult button constructor
	Button(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::string _text,
		std::shared_ptr<sf::Font> _font, sf::Color _fontColor, function _callBackFunction,
		GameHandler& _gameHandler);

	//Body getter ptr
	sf::RectangleShape getBody();

	//CallBack Function 
	void callback();
};