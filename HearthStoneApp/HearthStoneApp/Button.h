#pragma once
#include <SFML/Graphics.hpp>

typedef void (*function)(sf::RenderWindow*);

//Button class compatible with SFML
class Button : public sf::Drawable {
	
private:

	//Rectangle used to display button body
	sf::RectangleShape body;

	//Text used to display text on button
	sf::Text text;

	//Pointer to callback function
	function callBackFunction;

	//Pointer to window that button should be display on
	sf::RenderWindow* parentWindow;

	//Overwritten function from abstact drawable class
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:

	//Deafult button constructor
	Button(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::string _text, sf::Font &_font, sf::Color _fontColor, 
		function _callBackFunction, sf::RenderWindow* _parentWindow);

	//Body getter ptr
	sf::RectangleShape getBody();

	//CallBack Function 
	void callback();
};