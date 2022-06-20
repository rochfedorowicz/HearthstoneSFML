#include "dataHandler.h"

DataHandler::DataHandler() {};

bool DataHandler::loadFont(std::string _path, std::string _name) {
	if (fonts.find(_name) == fonts.end()) {
		fonts[_name] = std::make_shared<sf::Font>();
		if (fonts[_name]->loadFromFile(_path))
			return true;
		else return false;
	}
	else return false;
}

bool DataHandler::loadTexture(std::string _path, std::string _name) {
	if (textures.find(_name) == textures.end()) {
		textures[_name] = std::make_shared<sf::Texture>();
		if (textures[_name]->loadFromFile(_path))
			return true;
		else return false;
	}
	else return false;
}

std::shared_ptr<sf::Texture> DataHandler::getTexturePtr(std::string _nameOfTexture) {
	return textures[_nameOfTexture];
}

std::shared_ptr<sf::Font> DataHandler::getFontPtr(std::string _nameOfFont) {
	return fonts[_nameOfFont];
}

bool DataHandler::loadTextures(std::string _folderName) {
	auto texturesDirectory = std::filesystem::current_path();
	texturesDirectory += "\\" + _folderName;
	for (auto const& textureDirectory : std::filesystem::directory_iterator{ texturesDirectory })
	{
		if (!loadTexture(textureDirectory.path().string(),
			textureDirectory.path().filename().string().erase(textureDirectory.path().filename().string().find('.'))))
			return false;
	}
	return true;
}

bool DataHandler::reloadTextures(std::string _folderName) {
	textures.clear();
	return loadTextures(_folderName);
}

bool DataHandler::loadFonts(std::string _folderName) {
	auto texturesDirectory = std::filesystem::current_path();
	texturesDirectory += "\\" + _folderName;
	for (auto const& textureDirectory : std::filesystem::directory_iterator{ texturesDirectory })
	{
		if (!loadFont(textureDirectory.path().string(),
			textureDirectory.path().filename().string().erase(textureDirectory.path().filename().string().find('.'))))
			return false;
	}
	return true;
}

sf::Vector2i DataHandler::getLoadedTexturesResolution() {
	return loadedTexturesResolution;
}