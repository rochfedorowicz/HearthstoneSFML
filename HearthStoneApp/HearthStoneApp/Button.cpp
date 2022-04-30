#pragma once
#include "button.h"

Button::Button(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::string _text, 
	std::shared_ptr<sf::Font> _font, sf::Color _fontColor, CallbacksEnum _callBackFunction,
	std::shared_ptr<GameHandler> _gameHandler) : Interactive(_position, _size, _gameHandler) {

	body.setFillColor(_color);

	text = sf::Text(_text, *_font, _size.y/2);
	text.setOrigin(sf::Vector2f((text.getCharacterSize() * text.getString().getSize())/4, text.getCharacterSize()/1.5));
	auto textPosistion = sf::Vector2f(_position.x + 0.5 * _size.x, _position.y + 0.5 * _size.y);
	text.setPosition(textPosistion);
	text.setFillColor(_fontColor);

	callBackFunction = _callBackFunction;
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	Interactive::draw(target, states);
	if (isItClicked()) callback();
	gameHandler->getWindowPtr()->draw(text);
}

void Button::update() {}

void Button::callback() const{
	gameHandler->queueCallback(callBackFunction);
}