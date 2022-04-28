#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class GameHandler {
	sf::RenderWindow* currentWindowPtr;
	std::map<std::string, sf::Font> fonts;

public:
	GameHandler(sf::RenderWindow* _currentWindowPtr);

	bool loadFont(std::string _path, std::string _name);

	sf::Font getFontByName(std::string _nameOfFont);
};
