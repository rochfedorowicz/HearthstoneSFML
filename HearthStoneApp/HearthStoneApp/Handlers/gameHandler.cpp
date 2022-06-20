#pragma once
#include "gameHandler.h"
#include "../Interactive/button.h"
#include "../Cards/card.h"
#include "../Cards/cardPlacer.h"
#include "../Cards/militaryCard.h"
#include "../Cards/playerCard.h"
#include "../updateableBar.h"
#include "../updatableSprite.h"
#include "../updateableText.h"
#include "../selfUpdatableText.h"
#include "../Cards/slideableCardPlacer.h"
#include "../writtingField.h"

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
		hasJustFinished = false;
		wasKeyPressed = false;
		wasBackspacePressed = false;
		wasEnterPressed = false;
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
			if (event.type == sf::Event::KeyPressed) wasKeyPressed = true;
			if (event.type == sf::Event::TextEntered) enteredText = event.text.unicode;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) wasEnterPressed = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace)) wasBackspacePressed = true;
        }
		
		if (gameSatate == GameStateEnum::PLAY && roundsHandlerPtr->hasRoundFinished()) {
			hasJustFinished = true;
			roundsHandlerPtr->changeTurn();
			if (roundsHandlerPtr->getTurnOrder() == Turn::PLAYERS_TURN) playerHandlerPtr->renewMana();
			else opponentHandlerPtr->renewMana();
			roundsHandlerPtr->startRound();
		}

        currentWindowPtr->clear();
		checkCallbacks();

		for (auto& element : interfaceElements) {
			element->update(); 
		}

		for (auto& card : cards) {
			card->update();
			//TODO: Implement as an event invoked by picking card
			if (Card::getCurrentlyHeldCard().get() != nullptr &&
				card.get() == Card::getCurrentlyHeldCard().get() && card != cards.back())
				card.swap(cards.back());
			/////////////////////////////////////////////////////
			if (card->shouldBeDestroyed()) {
				disposeCardList.push_back(card);
			}
		}

        currentWindowPtr->display();

		for (int i = 0; i < disposeList.size(); ++i) {		
			for (auto j = interfaceElements.begin(); j != interfaceElements.end(); ++j) {
				if (*j == disposeList[i]) {
					interfaceElements.erase(j);
					break;
				}
			}
		}

		disposeList.clear();

		for (int i = 0; i < disposeCardList.size(); ++i) {
			for (auto j = cards.begin(); j != cards.end(); ++j) {
				if (*j == disposeCardList[i]) {
					cards.erase(j);
					break;
				}
			}
		}

		disposeCardList.clear();

		std::cout << playerHandlerPtr->getHealth() << " " << opponentHandlerPtr->getHealth();
		if (playerHandlerPtr->getHealth() == 0 || opponentHandlerPtr->getHealth() == 0) {
			gameSatate = GameStateEnum::NONE;
			currentWindowPtr->close();
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

		case GameStateEnum::PREPARING:
			currentWindowPtr = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "Heartstone: CHOOSE NAME'S", sf::Style::Titlebar);
			manageWindow();
			break;

		default: break;
	}
}

void GameHandler::appendDrawable(std::shared_ptr<Updatable> _updatablePtr) {
	interfaceElements.push_back(_updatablePtr);
}

void GameHandler::appendCard(std::shared_ptr<Updatable> _updatablePtr) {
	cards.push_back(_updatablePtr);
}


void GameHandler::disposeCard(std::shared_ptr<Updatable> _updatablePtr) {
	disposeCardList.push_back(_updatablePtr);
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
	while (!interfaceElements.empty()) interfaceElements.pop_back();
	while (!cards.empty()) cards.pop_back();
	switch (gameSatate){
		case GameStateEnum::MENU:
			ADD_INTERFACE_ELEMENT(UpdatableSprite, 0, 0, 640, 480, "menuBackgorund");
			ADD_INTERFACE_ELEMENT(Button, 120, 80, 400, 50, buttonBlueprints::PREPARE_GAMEPLAY_BUTTON);
			ADD_INTERFACE_ELEMENT(Button, 120, 180, 400, 50, buttonBlueprints::DISPLAY_SETTINGS_BUTTON);
			ADD_INTERFACE_ELEMENT(Button, 120, 280, 400, 50, buttonBlueprints::SHUT_DOWN_BUTTON);
			break;

		case GameStateEnum::SETTINGS:
			ADD_INTERFACE_ELEMENT(UpdatableSprite, 0, 0, 640, 480, "menuBackgorund");
			ADD_INTERFACE_ELEMENT(Button, 120, 80, 400, 50, buttonBlueprints::CHANGE_RESOLUTION_TO_1920_X_1080_BUTTON);
			ADD_INTERFACE_ELEMENT(Button, 120, 180, 400, 50, buttonBlueprints::CHANGE_RESOLUTION_TO_1280_X_720_BUTTON);
			ADD_INTERFACE_ELEMENT(Button, 120, 280, 400, 50, buttonBlueprints::DISPLAY_MENU_BUTTON);
			break;

		case GameStateEnum::PREPARING:
			ADD_INTERFACE_ELEMENT(UpdatableSprite, 0, 0, 640, 480, "chooseNamesBackground");
			ADD_INTERFACE_ELEMENT(WrittingField, 120, 80, 400, 50, 10, "Default name", "Matura", sf::Color::White, "[A-Z]{1}[a-z]{2,9}$", playerHandlerPtr->getPointerToName());
			ADD_INTERFACE_ELEMENT(WrittingField, 120, 180, 400, 50, 10, "Default name", "Matura", sf::Color::White, "[A-Z]{1}[a-z]{2,9}$", opponentHandlerPtr->getPointerToName());
			ADD_INTERFACE_ELEMENT(Button, 120, 280, 400, 50, buttonBlueprints::PLAY_GAME_BUTTON);
			break;

		case GameStateEnum::PLAY:
			 {
				float resCoeff = gameResolution.x == 1920 ? 1 : 2.0 / 3.0;
				std::shared_ptr<MilitaryCard> card = std::make_shared<MilitaryCard>(resCoeff * sf::Vector2f(280, 130),
					getTexturePtrByName(gameResolution.x == 1920 ? "cardTexture" : "cardTextureSmall"), 40, 3, 10, shared_from_this()),
					card2 = std::make_shared<MilitaryCard>(resCoeff * sf::Vector2f(280, 560),
						getTexturePtrByName(gameResolution.x == 1920 ? "cardTexture4" : "cardTexture4Small"), 100, 1, 10, shared_from_this()),
					card3 = std::make_shared<MilitaryCard>(resCoeff * sf::Vector2f(280, 1000),
						getTexturePtrByName(gameResolution.x == 1920 ? "cardTexture" : "cardTextureSmall"), 100, 1, 10, shared_from_this()),
					card4 = std::make_shared<MilitaryCard>(resCoeff * sf::Vector2f(500, 1000),
						getTexturePtrByName(gameResolution.x == 1920 ? "cardTexture4" : "cardTexture4Small"), 100, 1, 10, shared_from_this()),
					playerCard = std::make_shared<PlayerCard>(resCoeff * sf::Vector2f(20, 745),
						getTexturePtrByName(gameResolution.x == 1920 ? "cardTexture2" : "cardTexture2Small"), playerHandlerPtr, shared_from_this()),
					opponentsCard = std::make_shared<PlayerCard>(resCoeff * sf::Vector2f(20, 125),
						getTexturePtrByName(gameResolution.x == 1920 ? "cardTexture3" : "cardTexture3Small"), opponentHandlerPtr, shared_from_this());
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableBar, resCoeff, 260, 40, 1420, 60, BarType::HORIZONTAL, barBlueprints::ROUNDS_TIMER_BAR);
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableBar, resCoeff, 1830, 360, 60, 630, BarType::VERTICAL, barBlueprints::PLAYERS_MANA_BAR);
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableBar, resCoeff, 1730, 360, 60, 630, BarType::VERTICAL, barBlueprints::OPPONENTS_MANA_BAR);
				ADD_RESIZABLE_INTERFACE_ELEMENT(CardPlacer, resCoeff, 280, 130, 1400, 410, CardPlacerType::BATTLE_PLACE_OPPONENT,
					std::vector<std::shared_ptr<Card>> { card });
				ADD_RESIZABLE_INTERFACE_ELEMENT(CardPlacer, resCoeff, 280, 560, 1400, 410, CardPlacerType::BATTLE_PLACE_PLAYER,
					std::vector<std::shared_ptr<Card>> { card2 });
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableSprite, resCoeff, 0, 0, 1920, 1080, "background");
				ADD_RESIZABLE_INTERFACE_ELEMENT(CardPlacer, resCoeff, 20, 745, 160, 250, CardPlacerType::HERO_PLACE_PLAYER,
					std::vector<std::shared_ptr<Card>> { playerCard });
				ADD_RESIZABLE_INTERFACE_ELEMENT(CardPlacer, resCoeff, 20, 125, 160, 250, CardPlacerType::HERO_PLACE_OPPONENT,
					std::vector<std::shared_ptr<Card>> { opponentsCard });
				ADD_RESIZABLE_INTERFACE_ELEMENT(Button, resCoeff, 1730, 40, 160, 50, buttonBlueprints::SKIP_ROUND_BUTTON);
				ADD_RESIZABLE_INTERFACE_ELEMENT(Button, resCoeff, 1730, 120, 160, 50, buttonBlueprints::DISPLAY_MENU_BUTTON);
				ADD_RESIZABLE_INTERFACE_ELEMENT(Button, resCoeff, 1730, 200, 160, 50, buttonBlueprints::SHUT_DOWN_BUTTON);
				ADD_RESIZABLE_INTERFACE_ELEMENT(Button, resCoeff, 1730, 280, 160, 50, buttonBlueprints::TEST_BUTTON);
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableText, resCoeff, 280, -10, 200, 60, "Rounds timer", getFontPtrByName("Matura"), sf::Color::Black);
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableText, resCoeff, 20, 490, 250, 70, "It is turn of", getFontPtrByName("Matura"), sf::Color::Black);
				ADD_RESIZABLE_INTERFACE_ELEMENT(SelfUpdatableText, resCoeff, 0, 530, 220, 100, getFontPtrByName("Matura"), sf::Color::Black,
					std::make_shared<std::function<std::string(std::shared_ptr<GameHandler>)>>(&getValueFunctions::getRoundsOwner));
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableText, resCoeff, 1710, 850, 200, 60, "Player's mana", getFontPtrByName("Matura"), sf::Color::Black, -90.0f);
				ADD_RESIZABLE_INTERFACE_ELEMENT(UpdatableText, resCoeff, 1610, 840, 200, 60, "Opponent's mana", getFontPtrByName("Matura"), sf::Color::Black, -90.0f);
				ADD_RESIZABLE_INTERFACE_ELEMENT(SlideableCardPlacer, resCoeff, 280, 1000, 1400, 300, resCoeff * -180, "slideableDesk", MoveType::VERTICAL,
					std::vector<std::shared_ptr<Card>> { card3 }, std::vector<std::shared_ptr<Card>> { card4 });
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
