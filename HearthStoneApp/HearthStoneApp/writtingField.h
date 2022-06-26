#pragma once
#ifndef WRITTING_FIELD
#define WRITTING_FIELD
#include <regex>
#include "Interactive/interactive.h"
#include "updateableText.h"

/** Interactove class that allows us to fill it with text from keyboard. */
class WrittingField : public Interactive {

	/** Text to be displayed. */
	UpdatableText textToDisplay;

	/** Logic value indicating if writting field is active. */
	bool isActive;

	/** Maximal length of characters that will be displayed. */
	size_t maxLength;

	/** Regex expresion used for content checking. */
	std::regex regex;

	/** Function trying to append keyboard text. */
	void attemptToAppend(sf::String _newContent);

	/** Function deleting las character. */
	void deleteLastCharacter();

	/** Pointer to content. */
	std::shared_ptr<std::string> storePointer;
	
public:
	
	/** Main constructor. */
	WrittingField(sf::Vector2f _position, sf::Vector2f _size, size_t _maxLength, std::string _text, std::string _fontName,
		sf::Color _fontColor, std::string _regexFormula, std::shared_ptr<std::string> _storePointer, std::shared_ptr<GameHandler> _gameHandler);

	/** Function updating state of object and maintaing it. */
	void update();
	
};
#endif