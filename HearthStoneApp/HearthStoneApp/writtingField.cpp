#include "writtingField.h"

WrittingField::WrittingField(sf::Vector2f _position, sf::Vector2f _size, size_t _maxLength, std::string _text, std::string _fontName,
	sf::Color _fontColor, std::string _regexFormula, std::shared_ptr<std::string> _storePointer, std::shared_ptr<GameHandler> _gameHandler) :
	Interactive(_position, _size, sf::Color::Transparent, _gameHandler) {
	textToDisplay =  UpdatableText(_position, _size, _text, _gameHandler->getFontPtrByName(_fontName), _fontColor, _gameHandler);
	isActive = false;
	maxLength = _maxLength;
	regex = std::regex(_regexFormula);
	storePointer = _storePointer;
}

void WrittingField::attemptToAppend(sf::String _newContent) {
	char characterToBeAppend = *_newContent.begin();
	if (characterToBeAppend > 33)
		textToDisplay.contentUpdate(textToDisplay.getContent() + _newContent);
}

void WrittingField::deleteLastCharacter() {
	textToDisplay.contentUpdate(textToDisplay.getContent().substring(0, textToDisplay.getContent().getSize() - 1));
}

void WrittingField::update() {
	if (isActive) body.setFillColor(sf::Color::Red);
	if (isItClicked() && !isActive) isActive = true;
	else if (gameHandler->isMousePressed() && !isCursorHoverdOver() && isActive) isActive = false;
	if (isActive) {
		if (gameHandler->wasKeyPressed) {
			if (gameHandler->wasEnterPressed) {
				std::smatch m;
				std::string content = static_cast<std::string>(textToDisplay.getContent());
				if (std::regex_match(content, m, regex)) {
					body.setFillColor(sf::Color::Green);
					isActive = false;
					*storePointer = content;
				}
			}
			else if (gameHandler->wasBackspacePressed)
				deleteLastCharacter();
			else if (textToDisplay.getContent().getSize() < maxLength)
				attemptToAppend(gameHandler->enteredText);
		}
	}
	gameHandler->getWindowPtr()->draw(body);
	textToDisplay.update();
}