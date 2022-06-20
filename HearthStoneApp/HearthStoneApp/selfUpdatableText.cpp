#include "selfUpdatableText.h"

SelfUpdatableText::SelfUpdatableText(sf::Vector2f _position, sf::Vector2f _size, std::shared_ptr<sf::Font> _font,
	sf::Color _fontColor, std::shared_ptr<std::function<std::string(std::shared_ptr<GameHandler>)>> _getValueFunction,
	std::shared_ptr<GameHandler> _gameHandler) : UpdatableText(_position, _size, "", _font, _fontColor, _gameHandler) {
	getValueFunction = _getValueFunction;
}

void SelfUpdatableText::update() {
	UpdatableText::update();
	contentUpdate(getValueFunction->operator()(gameHandler));
}

bool SelfUpdatableText::shouldBeDestroyed() {
	return false;
}