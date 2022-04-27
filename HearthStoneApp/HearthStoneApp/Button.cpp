#include "Button.h"

Button::Button(sf::Vector2f _position, sf::Color _color, std::string _text, sf::RenderWindow *_parentWindow) {
	body = sf::RectangleShape(sf::Vector2f(_position.x, _position.y));
	body.setFillColor(_color);
	text = sf::Text()
	text.setString(_text);
	parentWindow = _parentWindow;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	parentWindow->draw(body);
	parentWindow->draw(text);
}