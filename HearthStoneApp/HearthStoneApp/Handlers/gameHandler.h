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

/** Enum indicating current game state. */
enum class GameStateEnum { MENU, PLAY, SETTINGS, PREPARING, FINISHING_SCREEN, NONE};

/** Class used for game handling. Has the biggest resposibilit in the whole project. */
class GameHandler : public std::enable_shared_from_this<GameHandler> {

	/** Pointer to current used window. */
	std::shared_ptr<sf::RenderWindow> currentWindowPtr;

	/** Pointer to hanlders resposible for player's and opponent's handling. */
	std::shared_ptr<PlayerHandler> playerHandlerPtr, opponentHandlerPtr;

	/** Pointer to round's hanlder. */
	std::shared_ptr<RoundsHandler> roundsHandlerPtr;

	/** Pointer to data's hanlder. */
	std::shared_ptr<DataHandler> dataHandlerPtr;

	/** Queue of callbacks. */
	std::queue<std::shared_ptr<std::function<void(std::shared_ptr<GameHandler>)>>> callbacksQueue;

	/** Mouse position. */
	sf::Vector2f mousePosition;

	/** Mouse clicked information. */
	bool mouseClicked;

	/** Mouse pressed information. */
	bool mousePressed;

	/** Mouse just released information. */
	bool mouseReleased;

	/** Logic value indicating if the round has just finished. */
	bool hasJustFinished;

	/** Logic value indicating if any key was pressed recently. */
	bool wasKeyPressed;

	/** Logic value indicating if backspace key was pressed. */
	bool wasBackspacePressed;

	/** Logic value indicating if backspace key was pressed. */
	bool wasEnterPressed;

	/** Text just entered by keyboard. */
	sf::String enteredText;

	/** Current game state. */
	GameStateEnum gameSatate;

	/** Current game resolution. */
	sf::Vector2i gameResolution;

	/** Vector of interface elements, cards and disposeLists working with them. */
	std::vector<std::shared_ptr<Updatable>> interfaceElements, cards, disposeList, disposeCardList;

	/** Function for chechikng queue of waiting callbacks. */
	void checkCallbacks();

	/** Loading grapchical interface elements required for current game state. */
	void loadGUIforGamestate();

public:

	/** Default's constructor, invoking it creates a window. */
	GameHandler();

	/** Font getter, using data handler object. */
	std::shared_ptr<sf::Font> getFontPtrByName(std::string _nameOfFont);

	/** Texture getter, using data handler object. */ 
	std::shared_ptr<sf::Texture> getTexturePtrByName(std::string _nameOfTexture);

	/** Current window pointer getter. */
	std::shared_ptr<sf::RenderWindow> getWindowPtr();

	/** Mouse position getter. */
	sf::Vector2f getMousePosition();

	/** Logic function checking if mouse was clicked. */
	bool isMouseClicked();

	/** Logic function checking if mouse was pressed. */
	bool isMousePressed();

	/** Logic function checking if mouse was released. */
	bool isMouseReleased();

	/** Function for window management. */
	void manageWindow();

	/** Function for chechikng queue of waiting callbacks. */
	void queueCallback(std::shared_ptr<std::function<void(std::shared_ptr<GameHandler>)>> _callback);

	/** Function adding new interface element. */
	void appendDrawable(std::shared_ptr<Updatable> _updatablePtr);

	/** Function adding new card. */
	void appendCard(std::shared_ptr<Updatable> _updatablePtr);

	/** Function adding card to card's dispose list. */
	void disposeCard(std::shared_ptr<Updatable> _updatablePtr);

	/** Getter for pointer to player's handler. */
	std::shared_ptr<PlayerHandler> getPlayerPtr();

	/** Getter for pointer to opponent's handler. */
	std::shared_ptr<PlayerHandler> getOpponentPtr();

	/** Getter for pointer to round's hanlder. */
	std::shared_ptr<RoundsHandler> getRoundHandlerPtr();

	/** Getter for pointer to data's hanlder. */
	std::shared_ptr<DataHandler> getDataHandlerPtr();

	/** Logic function checking if round has just finished. */
	bool hasRoundJustFinished();

	/** Function setting hasJustFinised logic value. */
	void setHasJustFinished(bool _newValue);

	/** Function checking if any key was pressed. */
	bool wasAnyKeyPressed();

	/** Function checking if backspace key was pressed. */
	bool wasBackspaceKeyPressed();

	/** Function checking if enter key was pressed. */
	bool wasEnterKeyPressed();

	/** Getter for entered text. */
	sf::String getEnteredText();
	
	/** Getter for game state. */
	GameStateEnum getGameState();

	/** Function setting game state. */
	void setGameState(GameStateEnum _newGameState);

	/** Getter for game resolution. */
	sf::Vector2i getGameResolution();

	/** Function setting game resolution. */
	void setGameResolution(sf::Vector2i _newResolution);
};
#endif

