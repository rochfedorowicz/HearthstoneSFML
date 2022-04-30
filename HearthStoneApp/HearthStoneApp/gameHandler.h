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

enum class CallbacksEnum { TEST_FN, SHUT_DOWN };

typedef void (*function)(std::shared_ptr<sf::RenderWindow>);

//Class used for game handling
class GameHandler {

	//Pointer to current used window
	std::shared_ptr<sf::RenderWindow> currentWindowPtr;

	//Map of used fonts
	std::map<std::string, std::shared_ptr<sf::Font>> fonts;

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

public:

	//Defaul constructor, invoking it creates a window
	GameHandler();

	//Function that allows us to load font from file
	bool loadFont(std::string _path, std::string _name);

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

	//Function adding button as drawable
	void appendDrawable(std::shared_ptr<Updatable> _updatablePtr);

	//Function for chechikng queue of waiting callbacks
	void checkCallbacks();

	//Function for chechikng queue of waiting callbacks
	void queueCallback(CallbacksEnum _functionEnum);
};
#endif

