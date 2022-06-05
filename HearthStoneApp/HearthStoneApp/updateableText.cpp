#include "updateableText.h"

UpdatabText::UpdatabText() {}

UpdatabText::UpdatabText(sf::Vector2f _position, sf::Vector2f _size, std::string _text,
	std::shared_ptr<sf::Font> _font, sf::Color _fontColor, std::shared_ptr<GameHandler> _gameHandler) {

	textToDisplay = sf::Text(_text, *_font, _size.y / 2);
	textToDisplay.setOrigin(sf::Vector2f((textToDisplay.getCharacterSize() * textToDisplay.getString().getSize()) / 4, textToDisplay.getCharacterSize() / 1.5));
	auto textPosistion = sf::Vector2f(_position.x + 0.5 * _size.x, _position.y + 0.5 * _size.y);
	textToDisplay.setPosition(textPosistion);
	textToDisplay.setFillColor(_fontColor);
	gameHandler = _gameHandler;

}

UpdatabText::UpdatabText(sf::Vector2f _position, float _size, std::string _text,
	std::shared_ptr<sf::Font> _font, sf::Color _fontColor, std::shared_ptr<GameHandler> _gameHandler) {

	textToDisplay = sf::Text(_text, *_font, _size / 2);
	textToDisplay.setOrigin(sf::Vector2f((textToDisplay.getCharacterSize() * textToDisplay.getString().getSize()) / 4, textToDisplay.getCharacterSize() / 1.5));
	textToDisplay.setPosition(_position);
	textToDisplay.setFillColor(_fontColor);
	gameHandler = _gameHandler;

}

void UpdatabText::update() {
	gameHandler->getWindowPtr()->draw(textToDisplay);
}

bool UpdatabText::shouldBeDestroyed() {
	return false;
}

void UpdatabText::contentUpdate(std::string _newContent) {
	textToDisplay.setString(_newContent);
}

void UpdatabText::positionUpdate(sf::Vector2f _change) {
	textToDisplay.setPosition(_change);
}