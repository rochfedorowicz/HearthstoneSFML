#pragma once
#include "buttonBlueprint.h"

ButtonBlueprint::ButtonBlueprint(std::string _name, sf::Color _color, std::string _fontName, sf::Color _fontColor,
	std::shared_ptr<std::function<void(std::shared_ptr<GameHandler>)>> _callbackFunction) :
	displayedName(_name), color(_color), fontName(_fontName), fontColor(_fontColor),
	callbackFunction(_callbackFunction) {};