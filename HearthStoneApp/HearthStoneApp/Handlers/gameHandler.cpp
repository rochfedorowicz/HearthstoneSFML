#pragma once
#include "gameHandler.h"
#include "../Interactive/button.h"
#include "../Cards/card.h"
#include "../Cards/cardPlacer.h"
#include "../Cards/militaryCard.h"
#include "../Cards/playerCard.h"
#include "../updateableBar.h"
//#include "../playerManaBar.h"
//#include "../roundsTimeBar.h"


GameHandler::GameHandler() {
	currentWindowPtr = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "Heartstone: MENU", sf::Style::Titlebar);
	gameSatate = GameStateEnum::MENU;
	gameResolution = sf::Vector2i(1920, 1080);
	player = std::make_shared<PlayerHandler>(10, 10, 100);
	opponent = std::make_shared<PlayerHandler>(10, 10, 100);
	roundsHandler = std::make_shared<RoundsHandler>(20);
}

bool GameHandler::loadFont(std::string _path, std::string _name) {
	if (fonts.find(_name) == fonts.end()) {
		fonts[_name] = std::make_shared<sf::Font>();
		if (fonts[_name]->loadFromFile(_path))
			return true;
		else return false;
	}
	else return false;
}

bool GameHandler::loadTexture(std::string _path, std::string _name) {
	if (textures.find(_name) == textures.end()) {
		textures[_name] = std::make_shared<sf::Texture>();
		if (textures[_name]->loadFromFile(_path)) 
			return true;
		else return false;
	}
	else return false;
}

std::shared_ptr<sf::Font> GameHandler::getFontPtrByName(std::string _nameOfFont) {
	return fonts[_nameOfFont];
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

		if (gameSatate == GameStateEnum::PLAY && roundsHandler->hasRoundFinished()) {
			roundsHandler->changeTurn();
			if (roundsHandler->getTurnOrder() == Turn::PLAYERS_TURN) player->renewMana();
			else opponent->renewMana();
			roundsHandler->startRound();
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
		callbacksQueue.front()(currentWindowPtr);
		callbacksQueue.pop();
	}
}

void GameHandler::queueCallback(CallbacksEnum _functionEnum) {
	switch (_functionEnum) {

		case CallbacksEnum::TEST_FN: 
			callbacksQueue.push(&callbacks::fn); 
			break;

		case CallbacksEnum::SHUT_DOWN: 
			gameSatate = GameStateEnum::NONE; 
			callbacksQueue.push(&callbacks::shutDown);
			break;

		case CallbacksEnum::PLAY_GAME: 
			gameSatate = GameStateEnum::PLAY;
			callbacksQueue.push(&callbacks::shutDown);
			break;

		case CallbacksEnum::DISPLAY_MENU: 
			gameSatate = GameStateEnum::MENU;
			callbacksQueue.push(&callbacks::shutDown);
			break;

		case CallbacksEnum::DISPLAY_SETTINGS:
			gameSatate = GameStateEnum::SETTINGS;
			callbacksQueue.push(&callbacks::shutDown);
			break;

		case CallbacksEnum::CHANGE_RESOLUTION_1920_X_1080:
			gameResolution = sf::Vector2i(1920, 1080);
			break;

		case CallbacksEnum::CHANGE_RESOLUTION_1280_X_720:
			gameResolution = sf::Vector2i(1280, 720);
			break;

		default: break;
	}
}

void GameHandler::loadGUIforGamestate() {
	switch (gameSatate){

		case GameStateEnum::MENU:
			while (!interfaceElements.empty()) interfaceElements.pop_back();
			appendDrawable(std::make_shared<Button>(sf::Vector2f(120, 80), sf::Vector2f(400, 50), buttonBlueprints::MAIN_STYLE_BUTTON,
				"Play", CallbacksEnum::PLAY_GAME, shared_from_this()));
			appendDrawable(std::make_shared<Button>(sf::Vector2f(120, 180), sf::Vector2f(400, 50), buttonBlueprints::MAIN_STYLE_BUTTON,
				"Settings", CallbacksEnum::DISPLAY_SETTINGS, shared_from_this()));
			appendDrawable(std::make_shared<Button>(sf::Vector2f(120, 280), sf::Vector2f(400, 50), buttonBlueprints::MAIN_STYLE_BUTTON,
				"Exit", CallbacksEnum::SHUT_DOWN, shared_from_this()));
			break;

		case GameStateEnum::SETTINGS:
			while (!interfaceElements.empty()) interfaceElements.pop_back();
			appendDrawable(std::make_shared<Button>(sf::Vector2f(120, 80), sf::Vector2f(400, 50), buttonBlueprints::MAIN_STYLE_BUTTON,
				"Change resolution to 1920x1080", CallbacksEnum::CHANGE_RESOLUTION_1920_X_1080, shared_from_this()));
			appendDrawable(std::make_shared<Button>(sf::Vector2f(120, 180), sf::Vector2f(400, 50), buttonBlueprints::MAIN_STYLE_BUTTON,
				"Change resolution to 1280x720", CallbacksEnum::CHANGE_RESOLUTION_1280_X_720, shared_from_this()));
			appendDrawable(std::make_shared<Button>(sf::Vector2f(120, 280), sf::Vector2f(400, 50), buttonBlueprints::MAIN_STYLE_BUTTON,
				"Go back", CallbacksEnum::DISPLAY_MENU, shared_from_this()));
			break;

		case GameStateEnum::PLAY:
			currentWindowPtr->setPosition(sf::Vector2i(0, 200));
			while (!interfaceElements.empty()) interfaceElements.pop_back(); {
				float resolutionCoefficient = gameResolution.x == 1920 ? 1 : 2.0 / 3.0;
				std::shared_ptr<MilitaryCard> card = std::make_shared<MilitaryCard>(resolutionCoefficient * sf::Vector2f(100, 100), textures[(gameResolution.x == 1920 ? "cardTexture" : "cardTextureSmall")], 40, 3, 10, shared_from_this()),
					card2 = std::make_shared<MilitaryCard>(resolutionCoefficient * sf::Vector2f(100, 500), textures[(gameResolution.x == 1920 ? "cardTexture" : "cardTextureSmall")], 100, 1, 10, shared_from_this()),
					playerCard = std::make_shared<PlayerCard>(resolutionCoefficient * sf::Vector2f(1700, 800), textures[(gameResolution.x == 1920 ? "cardTexture" : "cardTextureSmall")], player, shared_from_this());
				appendDrawable(std::make_shared<UpdatableRect>(resolutionCoefficient * sf::Vector2f(1700, 0), resolutionCoefficient * sf::Vector2f(220, 1080), sf::Color(149, 69, 53), shared_from_this()));
				appendDrawable(std::make_shared<UpdatableRect>(resolutionCoefficient * sf::Vector2f(0, 900), resolutionCoefficient * sf::Vector2f(1920, 180), sf::Color(149, 69, 53), shared_from_this()));
				appendDrawable(std::make_shared<UpdatableRect>(resolutionCoefficient * sf::Vector2f(0, 0), resolutionCoefficient * sf::Vector2f(1920, 40), sf::Color(149, 69, 53), shared_from_this()));
				appendDrawable(std::make_shared<UpdatableRect>(resolutionCoefficient * sf::Vector2f(0, 0), resolutionCoefficient * sf::Vector2f(40, 1080), sf::Color(149, 69, 53), shared_from_this()));
				appendDrawable(std::make_shared<Button>(resolutionCoefficient * sf::Vector2f(1730, 40), resolutionCoefficient * sf::Vector2f(160, 50), buttonBlueprints::MAIN_STYLE_BUTTON,
					"Save ", CallbacksEnum::TEST_FN, shared_from_this()));
				appendDrawable(std::make_shared<Button>(resolutionCoefficient * sf::Vector2f(1730, 120), resolutionCoefficient * sf::Vector2f(160, 50), buttonBlueprints::MAIN_STYLE_BUTTON,
					"Menu ", CallbacksEnum::DISPLAY_MENU, shared_from_this()));
				appendDrawable(std::make_shared<Button>(resolutionCoefficient * sf::Vector2f(1730, 200), resolutionCoefficient * sf::Vector2f(160, 50), buttonBlueprints::MAIN_STYLE_BUTTON,
					"Exit", CallbacksEnum::SHUT_DOWN, shared_from_this()));
				appendDrawable(std::make_shared<CardPlacer>(resolutionCoefficient * sf::Vector2f(100, 100), resolutionCoefficient * sf::Vector2f(1500, 300), CardPlacerType::BATTLE_PLACE_PLAYER,
					std::vector<std::shared_ptr<Card>> { card }, shared_from_this()));
				appendDrawable(std::make_shared<CardPlacer>(resolutionCoefficient * sf::Vector2f(100, 500), resolutionCoefficient * sf::Vector2f(1500, 300), CardPlacerType::BATTLE_PLACE_OPPONENT,
					std::vector<std::shared_ptr<Card>> { card2 }, shared_from_this()));
				appendDrawable(std::make_shared<CardPlacer>(resolutionCoefficient * sf::Vector2f(1700, 800), resolutionCoefficient * sf::Vector2f(160, 250), CardPlacerType::HERO_PLACE_PLAYER,
					std::vector<std::shared_ptr<Card>> { playerCard }, shared_from_this()));
				appendDrawable(std::make_shared<UpdatableBar>(resolutionCoefficient * sf::Vector2f(1740, 280), resolutionCoefficient * sf::Vector2f(60, 500), BarType::VERTICAL, barBlueprints::ROUNDS_TIMER_BAR, shared_from_this()));
				appendDrawable(std::make_shared<UpdatableBar>(resolutionCoefficient * sf::Vector2f(1830, 280), resolutionCoefficient * sf::Vector2f(60, 500), BarType::VERTICAL, barBlueprints::PLAYERS_MANA_BAR, shared_from_this()));
				appendDrawable(std::make_shared<UpdatableBar>(resolutionCoefficient * sf::Vector2f(1650, 280), resolutionCoefficient * sf::Vector2f(60, 500), BarType::VERTICAL, barBlueprints::OPPONENTS_MANA_BAR, shared_from_this()));
				appendDrawable(card);
				appendDrawable(card2);
				appendDrawable(playerCard);
				roundsHandler->startRound();
			}
			break;

		default: break;
	}
}


std::shared_ptr<PlayerHandler> GameHandler::getPlayerPtr() {
	return player;
}

std::shared_ptr<PlayerHandler> GameHandler::getOpponentPtr() {
	return opponent;
}

std::shared_ptr<RoundsHandler> GameHandler::getRoundHandlerPtr() {
	return roundsHandler;
}
