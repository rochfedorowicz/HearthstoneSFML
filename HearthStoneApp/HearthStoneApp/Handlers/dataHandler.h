#pragma once
#ifndef DATA_HANDLER
#define DATA_HANDLER
#include <filesystem>
#include <map>
#include <string>
#include <memory>
#include "SFML/Graphics.hpp"

class DataHandler {

	//Map of used fonts
	std::map<std::string, std::shared_ptr<sf::Font>> fonts;

	//Map of used texture
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;

	//Function that allows to load font from file
	bool loadFont(std::string _path, std::string _name);

	//Function that allows to load texture from file
	bool loadTexture(std::string _path, std::string _name);

public:

	DataHandler();

	std::shared_ptr<sf::Texture> getTexturePtr(std::string _nameOfTexture);

	std::shared_ptr<sf::Font> getFontPtr(std::string _nameOfFont);

	bool loadTextures(std::string _folderName);

	bool reloadTextures(std::string _folderName);

	bool loadFonts(std::string _folderName);

	sf::Vector2i loadedTexturesResolution;
};
#endif