#pragma once
#ifndef WRITTING_FIELD
#define WRITTING_FIELD
#include <regex>
#include "Interactive/interactive.h"
#include "updateableText.h"

class WrittingField : public Interactive {

	UpdatableText textToDisplay;

	bool isActive;

	size_t maxLength;

	std::regex regex;

	void attemptToAppend(sf::String _newContent);

	void deleteLastCharacter();

	std::shared_ptr<std::string> storePointer;
	
public:
	
	WrittingField(sf::Vector2f _position, sf::Vector2f _size, size_t _maxLength, std::string _text, std::string _fontName,
		sf::Color _fontColor, std::string _regexFormula, std::shared_ptr<std::string> _storePointer, std::shared_ptr<GameHandler> _gameHandler);

	void update();
	
};
#endif