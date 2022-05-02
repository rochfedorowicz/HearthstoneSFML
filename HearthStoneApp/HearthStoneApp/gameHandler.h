#pragma once
#ifndef GAME_HANDLER
#define GAME_HANDLER
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>
#include <queue>
#include <vector>
#include "callbacks.h"
#include "updatable.h"

//Enum indicating callback invoked
enum class CallbacksEnum { TEST_FN, SHUT_DOWN, PLAY_GAME, DISPLAY_MENU};

//Enum indicating current game state
enum class GameStateEnum { MENU, PLAY, NONE};

//Function pointer
typedef void (*function)(std::shared_ptr<sf::RenderWindow>);

//Class used for game handling
class GameHandler : public std::enable_shared_from_this<GameHandler> {

	//Pointer to current used window
	std::shared_ptr<sf::RenderWindow> currentWindowPtr;

	//Game state indicating enum
	GameStateEnum gameSatate;

	//Map of used fonts
	std::map<std::string, std::shared_ptr<sf::Font>> fonts;

	//Map of used texture
	std::map<std::string, std::shared_ptr<sf::Texture>> textures;

	//Queue of callbacks
	std::queue<function> callbacksQueue;

	//Mouse position
	sf::Vector2f mousePosition;

	//Mouse clicked information
	bool mouseClicked;

	//Mouse pressed information
	bool mousePressed;

	//Vector of drawables
	std::vector<std::shared_ptr<Updatable>> interfaceElements;

	//Function for chechikng queue of waiting callbacks
	void checkCallbacks();

	//Function adding new interface element
	void appendDrawable(std::shared_ptr<Updatable> _updatablePtr);

	//Loading grapchical interface elements required for current game state
	void loadGUIforGamestate();

public:

	//Defaul constructor, invoking it creates a window
	GameHandler();

	//Function that allows to load font from file
	bool loadFont(std::string _path, std::string _name);

	//Function that allows to load texture from file
	bool loadTexture(std::string _path, std::string _name);

	//Font getter 
	std::shared_ptr<sf::Font> getFontPtrByName(std::string _nameOfFont);

	//Current window pointer getter
	std::shared_ptr<sf::RenderWindow> getWindowPtr();

	//Mouse position getter
	sf::Vector2f getMousePosition();

	//Logic function checking if mouse was clicked
	bool isMouseClicked();

	//Logic function checking if mouse was clicked
	bool isMousePressed();

	//Function for window management
	void manageWindow();

	//Function for chechikng queue of waiting callbacks
	void queueCallback(CallbacksEnum _functionEnum);
};
#endif

