#pragma once
#include "gameHandler.h"

GameHandler::GameHandler(sf::RenderWindow* _currentWindowPtr) {
	currentWindowPtr = _currentWindowPtr;
}

bool GameHandler::loadFont(std::string _path, std::string _name) {
	if (fonts.find(_name) == fonts.end()) {
		fonts[_name] = sf::Font();
		if (fonts[_name].loadFromFile(_path))
			return true;
		else return false;
	}
	else return false;
}

sf::Font GameHandler::getFontByName(std::string _nameOfFont) {
	return fonts[_nameOfFont];
}
