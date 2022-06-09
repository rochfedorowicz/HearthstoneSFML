#pragma once
#include "button.h"

Button::Button(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, std::string _text, 
	std::shared_ptr<sf::Font> _font, sf::Color _fontColor, std::shared_ptr<std::function<void(std::shared_ptr<GameHandler>)>> _callBackFunction,
	std::shared_ptr<GameHandler> _gameHandler) : Interactive(_position, _size, _color, _gameHandler) {

	text = sf::Text(_text, *_font, _size.y/2);
	text.setOrigin(sf::Vector2f((text.getCharacterSize() * text.getString().getSize())/4, text.getCharacterSize()/1.5));
	auto textPosistion = sf::Vector2f(_position.x + 0.5 * _size.x, _position.y + 0.5 * _size.y);
	text.setPosition(textPosistion);
	text.setFillColor(_fontColor);

	callBackFunction = _callBackFunction;
}

Button::Button(sf::Vector2f _position, sf::Vector2f _size, ButtonBlueprint _bluePrint, std::shared_ptr<GameHandler> _gameHandler)
	: Button(_position, _size, _bluePrint.color, _bluePrint.displayedName, _gameHandler->getFontPtrByName(_bluePrint.fontName),
	_bluePrint.fontColor, _bluePrint.callbackFunction, _gameHandler) {};

void Button::update() {
	Interactive::update();
	if (isItClicked()) callback();
	gameHandler->getWindowPtr()->draw(text);
}

void Button::callback() {
	gameHandler->queueCallback(callBackFunction);
}