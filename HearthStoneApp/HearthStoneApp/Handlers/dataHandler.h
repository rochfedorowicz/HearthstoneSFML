#pragma once
#ifndef DATA_HANDLER
#define DATA_HANDLER
#include <filesystem>
#include <map>
#include <string>
#include <memory>
#include "SFML/Graphics.hpp"

/** Class resposinble for data handling across the project. */
class DataHandler {

	/** Map of used fonts. */
	std::map<std::string, std::shared_ptr<sf::Font>> fonts;

	/** Map of used texture. */
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;

	/** Function that allows to load font from file. */
	bool loadFont(std::string _path, std::string _name);

	/** Function that allows to load texture from file. */
	bool loadTexture(std::string _path, std::string _name);

	/** Value indicating resolution of currenlty loaded texture's set. */
	sf::Vector2i loadedTexturesResolution;

public:

	/** Deafult's constructor. */
	DataHandler();

	/** Getter to texture's pointer specified by name in argument. */
	std::shared_ptr<sf::Texture> getTexturePtr(std::string _nameOfTexture);

	/** Getter to font's pointer specified by name in argument. */
	std::shared_ptr<sf::Font> getFontPtr(std::string _nameOfFont);

	/** Function that allows to load all textures from specified directory. */
	bool loadTextures(std::string _folderName);

	/** Function that allows to reload all textures from specified directory. */
	bool reloadTextures(std::string _folderName);

	/** Function that allows to load all fonts from specified directory. */
	bool loadFonts(std::string _folderName);

	/** Getter to value indicating resolution of currenlty loeaded texture's set. */
	sf::Vector2i getLoadedTexturesResolution();
};
#endif