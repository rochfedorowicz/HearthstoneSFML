#include "updateableText.h"

UpdatableText::UpdatableText() {}

UpdatableText::UpdatableText(sf::Vector2f _position, sf::Vector2f _size, std::string _text,
	std::shared_ptr<sf::Font> _font, sf::Color _fontColor, std::shared_ptr<GameHandler> _gameHandler) {

	textToDisplay = sf::Text(_text, *_font, _size.y / 2);
	textToDisplay.setOrigin(sf::Vector2f((textToDisplay.getCharacterSize() * textToDisplay.getString().getSize()) / 4, textToDisplay.getCharacterSize() / 1.5));
	auto textPosistion = sf::Vector2f(_position.x + 0.5 * _size.x, _position.y + 0.5 * _size.y);
	textToDisplay.setPosition(textPosistion);
	textToDisplay.setFillColor(_fontColor);
	gameHandler = _gameHandler;

}

UpdatableText::UpdatableText(sf::Vector2f _position, float _size, std::string _text,
	std::shared_ptr<sf::Font> _font, sf::Color _fontColor, std::shared_ptr<GameHandler> _gameHandler) {

	textToDisplay = sf::Text(_text, *_font, _size / 2);
	textToDisplay.setOrigin(sf::Vector2f((textToDisplay.getCharacterSize() * textToDisplay.getString().getSize()) / 4, textToDisplay.getCharacterSize() / 1.5));
	textToDisplay.setPosition(_position);
	textToDisplay.setFillColor(_fontColor);
	gameHandler = _gameHandler;

}

UpdatableText::UpdatableText (sf::Vector2f _position, sf::Vector2f _size, std::string _text, std::shared_ptr<sf::Font> _font,
	sf::Color _fontColor, float _angle, std::shared_ptr<GameHandler> _gameHandler) 
	: UpdatableText(_position, _size, _text, _font, _fontColor, _gameHandler) {

	textToDisplay.rotate(_angle);
}

void UpdatableText::update() {
	gameHandler->getWindowPtr()->draw(textToDisplay);
}

bool UpdatableText::shouldBeDestroyed() {
	return false;
}

void UpdatableText::contentUpdate(std::string _newContent) {
	textToDisplay.setString(_newContent);
}

void UpdatableText::positionUpdate(sf::Vector2f _change) {
	textToDisplay.setPosition(_change);
}