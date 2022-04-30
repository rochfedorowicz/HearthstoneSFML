#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>

//Class used for game handling
class GameHandler {

	//Pointer to current used window
	std::shared_ptr<sf::RenderWindow> currentWindowPtr;

	//Map of used fonts
	std::map<std::string, std::shared_ptr<sf::Font>> fonts;

public:

	//Defaul constructor, invoking it creates a window
	GameHandler();

	//Function that allows us to load font from file
	bool loadFont(std::string _path, std::string _name);

	//Font getter 
	std::shared_ptr<sf::Font> getFontPtrByName(std::string _nameOfFont);

	//Current window pointer getter
	std::shared_ptr<sf::RenderWindow> getWindowPtr();
};
