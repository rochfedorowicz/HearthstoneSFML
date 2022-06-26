#pragma once
#ifndef UPDATABLE_TEXT
#define UPDATABLE_TEXT
#include <SFML/Graphics.hpp>
#include "Handlers/gameHandler.h"
#include "Interfaces/updatable.h"


/** Class being adaptation of text from SFML that can work with game handler properly. */
class UpdatableText: public Updatable {

	/** Text do be displayed */
	sf::Text textToDisplay;

	/** Fucntion repositioning object. */
	void reposition();

protected:
	/** Parent game handler */
	std::shared_ptr<GameHandler> gameHandler;

public:

	/** Default constructor. */
	UpdatableText();

	/** Main constructor. Setting the text at the center of rectangle described by
	* the position and size parameter.  */
	UpdatableText(sf::Vector2f _position, sf::Vector2f _size, std::string _text, std::shared_ptr<sf::Font> _font,
		sf::Color _fontColor, std::shared_ptr<GameHandler> _gameHandler);

	/** Main constructor. Setting the text at the center of rectangle described by
	* the position and size parameter and rotating it particular by angle. */
	UpdatableText(sf::Vector2f _position, sf::Vector2f _size, std::string _text, std::shared_ptr<sf::Font> _font,
		sf::Color _fontColor, float _angle, std::shared_ptr<GameHandler> _gameHandler);

	/** Main constructor. Setting the text at the exact position specified by position parameter 
	* and displaying it with particular size. */
	UpdatableText(sf::Vector2f _position, float _size, std::string _text, std::shared_ptr<sf::Font> _font,
		sf::Color _fontColor, std::shared_ptr<GameHandler> _gameHandler);

	/** Overwritten function from abstact updatable class */
	void update();

	/** Overwritten function from abstact updatable class */
	bool shouldBeDestroyed();

	/** Function updating content of text. */
	void contentUpdate(const sf::String _newContent);

	/** Function geting content of text. */
	const sf::String getContent();

	/** Function updating position of object. */
	void positionUpdate(sf::Vector2f _change);

};
#endif