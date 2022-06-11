#pragma once
#ifndef GAME_HANDLER
#define GAME_HANDLER
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
#include <queue>
#include <vector>
#include <functional>
#include "../Interfaces/updatable.h"
#include "roundsHandler.h"
#include "playerHandler.h"
#include "dataHandler.h"

//Enum indicating current game state
enum class GameStateEnum { MENU, PLAY, SETTINGS, NONE};

//Class used for game handling
class GameHandler : public std::enable_shared_from_this<GameHandler> {

	//Pointer to current used window
	std::shared_ptr<sf::RenderWindow> currentWindowPtr;

	std::shared_ptr<PlayerHandler> playerHandlerPtr, opponentHandlerPtr;

	std::shared_ptr<RoundsHandler> roundsHandlerPtr;

	std::shared_ptr<DataHandler> dataHandlerPtr;

	//Queue of callbacks
	std::queue<std::shared_ptr<std::function<void(std::shared_ptr<GameHandler>)>>> callbacksQueue;

	//Mouse position
	sf::Vector2f mousePosition;

	//Mouse clicked information
	bool mouseClicked;

	//Mouse pressed information
	bool mousePressed;

	//Mouse just released information
	bool mouseReleased;

	//Vector of drawables
	std::vector<std::shared_ptr<Updatable>> interfaceElements, disposeList;

	//Function for chechikng queue of waiting callbacks
	void checkCallbacks();

	//Loading grapchical interface elements required for current game state
	void loadGUIforGamestate();

public:

	//Game state indicating enum should be private
	GameStateEnum gameSatate;

	//Should be private tooo!!!!
	sf::Vector2i gameResolution;

	//Defaul constructor, invoking it creates a window
	GameHandler();

	//Font getter 
	std::shared_ptr<sf::Font> getFontPtrByName(std::string _nameOfFont);

	//Texture getter 
	std::shared_ptr<sf::Texture> getTexturePtrByName(std::string _nameOfTexture);

	//Current window pointer getter
	std::shared_ptr<sf::RenderWindow> getWindowPtr();

	//Mouse position getter
	sf::Vector2f getMousePosition();

	//Logic function checking if mouse was clicked
	bool isMouseClicked();

	//Logic function checking if mouse was clicked
	bool isMousePressed();

	//Logic function checking if mouse was released
	bool isMouseReleased();

	//Function for window management
	void manageWindow();

	//Function for chechikng queue of waiting callbacks
	void queueCallback(std::shared_ptr<std::function<void(std::shared_ptr<GameHandler>)>> _callback);

	//Function adding new interface element
	void appendDrawable(std::shared_ptr<Updatable> _updatablePtr);

	std::shared_ptr<PlayerHandler> getPlayerPtr();

	std::shared_ptr<PlayerHandler> getOpponentPtr();

	std::shared_ptr<RoundsHandler> getRoundHandlerPtr();

	std::shared_ptr<DataHandler> getDataHandlerPtr();
};
#endif

