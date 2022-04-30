#pragma once
#include "gameHandler.h"

GameHandler::GameHandler() {
	currentWindowPtr = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "This app", sf::Style::Titlebar);
}

bool GameHandler::loadFont(std::string _path, std::string _name) {
	if (fonts.find(_name) == fonts.end()) {
		fonts[_name] = std::make_shared<sf::Font>();
		if (fonts[_name]->loadFromFile(_path))
			return true;
		else return false;
	}
	else return false;
}

std::shared_ptr<sf::Font> GameHandler::getFontPtrByName(std::string _nameOfFont) {
	return fonts[_nameOfFont];
}

std::shared_ptr<sf::RenderWindow> GameHandler::getWindowPtr() {
	return currentWindowPtr;
}
