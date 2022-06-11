#pragma once
#include "gameHandler.h"
#include "../Interactive/button.h"
#include "../Cards/card.h"
#include "../Cards/cardPlacer.h"
#include "../Cards/militaryCard.h"
#include "../Cards/playerCard.h"
#include "../updateableBar.h"

#define ADD_RESIZABLE_INTERFACE_ELEMENT(type, resCoeff, posX, posY, sizeX, sizeY, ...) \
appendDrawable(std::make_shared<type>(resCoeff * sf::Vector2f(posX, posY), resCoeff * sf::Vector2f(sizeX, sizeY),\
	__VA_ARGS__, shared_from_this()))
#define ADD_INTERFACE_ELEMENT(type, posX, posY, sizeX, sizeY, ...) ADD_RESIZABLE_INTERFACE_ELEMENT(type,\
	1.0f, posX, posY, sizeX, sizeY, __VA_ARGS__)

GameHandler::GameHandler() {
	currentWindowPtr = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "Heartstone: MENU", sf::Style::Titlebar);
	gameSatate = GameStateEnum::MENU;
	gameResolution = sf::Vector2i(1920, 1080);
	playerHandlerPtr = std::make_shared<PlayerHandler>(10, 10, 100);
	opponentHandlerPtr = std::make_shared<PlayerHandler>(10, 10, 100);
	roundsHandlerPtr = std::make_shared<RoundsHandler>(20);
	dataHandlerPtr = std::make_shared<DataHandler>();
}

std::shared_ptr<sf::Font> GameHandler::getFontPtrByName(std::string _nameOfFont) {
	return dataHandlerPtr->getFontPtr(_nameOfFont);
}

std::shared_ptr<sf::Texture> GameHandler::getTexturePtrByName(std::string _nameOfTexture) {
	return dataHandlerPtr->getTexturePtr(_nameOfTexture);
}

std::shared_ptr<sf::RenderWindow> GameHandler::getWindowPtr() {
	return currentWindowPtr;
}

sf::Vector2f GameHandler::getMousePosition() {
	return mousePosition;
}

bool GameHandler::isMouseClicked() {
	return mouseClicked;
}

bool GameHandler::isMousePressed() {
	return mousePressed;
}

bool GameHandler::isMouseReleased() {
	return mouseReleased;
}

void GameHandler::manageWindow() {
	loadGUIforGamestate();
	mousePressed = false;
    while (currentWindowPtr->isOpen())
    {
        mouseClicked = false;
		mouseReleased = false;
        sf::Event event;
        while (currentWindowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed) mouseClicked = true;
			if (event.type == sf::Event::MouseMoved) {
				mousePosition.x = event.mouseMove.x;
				mousePosition.y = event.mouseMove.y;
			}	
			if (event.type == sf::Event::MouseButtonPressed) mousePressed = true;
			if (event.type == sf::Event::MouseButtonReleased) {
				mousePressed = false;
				mouseReleased = true;
			}
        }
        currentWindowPtr->clear();
		checkCallbacks();
		for (auto& element : interfaceElements) {
			element->update(); 
			//TODO: Implement as an event invoked by picking card
			if (Card::getCurrentlyHeldCard().get() != nullptr &&
				element.get() == Card::getCurrentlyHeldCard().get() && element != interfaceElements.back())
				element.swap(interfaceElements.back());
			/////////////////////////////////////////////////////
			if (element->shouldBeDestroyed()) {
				disposeList.push_back(element);
			}
		}
        currentWindowPtr->display();

		if (gameSatate == GameStateEnum::PLAY && roundsHandlerPtr->hasRoundFinished()) {
			roundsHandlerPtr->changeTurn();
			if (roundsHandlerPtr->getTurnOrder() == Turn::PLAYERS_TURN) playerHandlerPtr->renewMana();
			else opponentHandlerPtr->renewMana();
			roundsHandlerPtr->startRound();
		}

		for (int i = 0; i < disposeList.size(); ++i) {		
			for (auto j = interfaceElements.begin(); j != interfaceElements.end(); ++j) {
				if (*j == disposeList[i]) {
					interfaceElements.erase(j);
					break;
				}
			}
		}
    }
	switch (gameSatate) {

		case GameStateEnum::PLAY:
			currentWindowPtr = std::make_shared<sf::RenderWindow>(sf::VideoMode(gameResolution.x, gameResolution.y), "Heartstone", sf::Style::Titlebar);
			manageWindow();
			break;

		case GameStateEnum::MENU:
			currentWindowPtr = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "Heartstone: MENU", sf::Style::Titlebar);
			manageWindow();
			break;

		case GameStateEnum::SETTINGS:
			currentWindowPtr = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "Heartstone: SETTINGS", sf::Style::Titlebar);
			manageWindow();
			break;

		default: break;
	}
}

void GameHandler::appendDrawable(std::shared_ptr<Updatable> _updatablePtr) {
	interfaceElements.push_back(_updatablePtr);
}

void GameHandler::checkCallbacks() {
	while (!callbacksQueue.empty()) {
		callbacksQueue.front()->operator()(shared_from_this());
		callbacksQueue.pop();
	}
}

void GameHandler::queueCallback(std::shared_ptr<std::function<void(std::shared_ptr<GameHandler>)>> _callback) {
	callbacksQueue.push(_callback);
}

void GameHandler::loadGUIforGamestate() {
	switch (gameSatate){
		case GameStateEnum::MENU:
			while (!interfaceElements.empty()) interfaceElements.pop_back();
			ADD_INTERFACE_ELEMENT(Button, 120, 80, 400, 50, buttonBlueprints::PLAY_GAME_BUTTON);
			ADD_INTERFACE_ELEMENT(Button, 120, 180, 400, 50, buttonBlueprints::DISPLAY_SETTINGS_BUTTON);
			ADD_INTERFACE_ELEMENT(Button, 120, 280, 400, 50, buttonBlueprints::SHUT_DOWN_BUTTON);
			break;

		case GameStateEnum::SETTINGS:
			while (!interfaceElements.empty()) interfaceElements.pop_back();
			ADD_INTERFACE_ELEMENT(Button, 120, 80, 400, 50, buttonBlueprints::CHANGE_RESOLUTION_TO_1920_X_1080_BUTTON);
			ADD_INTERFACE_ELEMENT(Button, 120, 180, 400, 50, buttonBlueprints::CHANGE_RESOLUTION_TO_1280_X_720_BUTTON);
			ADD_INTERFACE_ELEMENT(Button, 120, 280, 400, 50, buttonBlueprints::DISPLAY_MENU_BUTTON);
			break;

		case GameStateEnum::PLAY:
			while (!interfaceElements.empty()) interfaceElements.pop_back(); {
				float resCoeff = gameResolution.x == 1920 ? 1 : 2.0 / 3.0;
				std::shared_ptr<MilitaryCard> card = std::make_shared<MilitaryCard>(resCoeff * sf::Vector2f(100, 100), getTexturePtrByName(gameResolution.x == 1920 ? "cardTexture" : "cardTextureSmall"), 40, 3, 10, shared_from_this()),
					card2 = std::make_shared<MilitaryCard>(resCoeff * sf::Vector2f(100, 500), getTexturePtrByName(gameResolution.x == 1920 ? "cardTexture" : "cardTextureSmall"), 100, 1, 10, shared_from_this()),
					playerCard = std::make_shared<PlayerCard>(resCoeff * sf::Vector2f(1700, 800), getTexturePtrByName(gameResolution.x == 1920 ? "cardTexture" : "cardTextureSmall"), playerHandlerPtr, shared_from_this());
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableRect, resCoeff, 1700, 0, 220, 1080, colorBlueprints::BACKGROUND_BROWN);
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableRect, resCoeff, 0, 900, 1920, 180, colorBlueprints::BACKGROUND_BROWN);
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableRect, resCoeff, 0, 0, 1920, 40, colorBlueprints::BACKGROUND_BROWN);
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableRect, resCoeff, 0, 0, 40, 1080, colorBlueprints::BACKGROUND_BROWN);
				ADD_RESIZABLE_INTERFACE_ELEMENT(Button, resCoeff, 1730, 40, 160, 50, buttonBlueprints::TEST_BUTTON);
				ADD_RESIZABLE_INTERFACE_ELEMENT(Button, resCoeff, 1730, 120, 160, 50, buttonBlueprints::DISPLAY_MENU_BUTTON);
				ADD_RESIZABLE_INTERFACE_ELEMENT(Button, resCoeff, 1730, 200, 160, 50, buttonBlueprints::SHUT_DOWN_BUTTON);
				ADD_RESIZABLE_INTERFACE_ELEMENT(CardPlacer, resCoeff, 100, 100, 1500, 300, CardPlacerType::BATTLE_PLACE_PLAYER,
					std::vector<std::shared_ptr<Card>> { card });
				ADD_RESIZABLE_INTERFACE_ELEMENT(CardPlacer, resCoeff, 100, 500, 1500, 300, CardPlacerType::BATTLE_PLACE_OPPONENT,
					std::vector<std::shared_ptr<Card>> { card2 });
				ADD_RESIZABLE_INTERFACE_ELEMENT(CardPlacer, resCoeff, 1700, 800, 160, 250, CardPlacerType::HERO_PLACE_PLAYER,
					std::vector<std::shared_ptr<Card>> { playerCard });
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableBar, resCoeff, 1740, 280, 60, 500, BarType::VERTICAL, barBlueprints::ROUNDS_TIMER_BAR);
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableBar, resCoeff, 1830, 280, 60, 500, BarType::VERTICAL, barBlueprints::PLAYERS_MANA_BAR);
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableBar, resCoeff, 1650, 280, 60, 500, BarType::VERTICAL, barBlueprints::OPPONENTS_MANA_BAR);
				appendDrawable(card);
				appendDrawable(card2);
				appendDrawable(playerCard);
				roundsHandlerPtr->startRound();
			}
			break;

		default: break;
	}
}


std::shared_ptr<PlayerHandler> GameHandler::getPlayerPtr() {
	return playerHandlerPtr;
}

std::shared_ptr<PlayerHandler> GameHandler::getOpponentPtr() {
	return opponentHandlerPtr;
}

std::shared_ptr<RoundsHandler> GameHandler::getRoundHandlerPtr() {
	return roundsHandlerPtr;
}

std::shared_ptr<DataHandler> GameHandler::getDataHandlerPtr() {
	return dataHandlerPtr;
}
