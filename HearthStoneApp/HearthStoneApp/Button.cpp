#include "button.h"

Button::Button(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::string _text, sf::Font& _font, sf::Color _fontColor,
	function _callBackFunction, sf::RenderWindow* _parentWindow) {

	//Creating body
	body = sf::RectangleShape(sf::Vector2f(_size.x, _size.y));
	body.setPosition(_position);
	body.setFillColor(_color);

	//Creating text
	text = sf::Text(_text, _font, _size.y/2);
	text.setOrigin(sf::Vector2f((text.getCharacterSize() * text.getString().getSize())/4, text.getCharacterSize()/1.5));
	auto textPosistion = sf::Vector2f(_position.x + 0.5 * _size.x, _position.y + 0.5 * _size.y);
	text.setPosition(textPosistion);
	text.setFillColor(_fontColor);

	callBackFunction = _callBackFunction;
	parentWindow = _parentWindow;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	parentWindow->draw(body);
	parentWindow->draw(text);
}

sf::RectangleShape Button::getBody() {
	return body;
}

void Button::callback() {
	callBackFunction(parentWindow);
}