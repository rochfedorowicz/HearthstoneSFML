#pragma once
#include "gameHandler.h"
#include "button.h"
#include "card.h"

GameHandler::GameHandler() {
	currentWindowPtr = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "Heartstone: MENU", sf::Style::Titlebar);
	gameSatate = GameStateEnum::MENU;
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

void GameHandler::manageWindow() {
	loadGUIforGamestate();
	mousePressed = false;
    while (currentWindowPtr->isOpen())
    {
        mouseClicked = false;
        sf::Event event;
        while (currentWindowPtr->pollEvent(event))
        {
            if (event.type == sf::Event::MouseButtonPressed) mouseClicked = true;
			if (event.type == sf::Event::MouseMoved) {
				mousePosition.x = event.mouseMove.x;
				mousePosition.y = event.mouseMove.y;
			}	
			if (event.type == sf::Event::MouseButtonPressed) mousePressed = true;
			else if (event.type == sf::Event::MouseButtonReleased) mousePressed = false;
        }
        currentWindowPtr->clear();
		checkCallbacks();
		for (auto& element : interfaceElements) element->update();
        currentWindowPtr->display();
    }
	switch (gameSatate) {

		case GameStateEnum::PLAY:
			currentWindowPtr = std::make_shared<sf::RenderWindow>(sf::VideoMode(1920, 1080), "Heartstone", sf::Style::Titlebar);
			manageWindow();
			break;

		case GameStateEnum::MENU:
			currentWindowPtr = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "Heartstone: MENU", sf::Style::Titlebar);
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
				"Display 1", CallbacksEnum::TEST_FN, shared_from_this()));
			appendDrawable(std::make_shared<Button>(sf::Vector2f(120, 280), sf::Vector2f(400, 50), buttonBlueprints::MAIN_STYLE_BUTTON,
				"Exit", CallbacksEnum::SHUT_DOWN, shared_from_this()));
			break;

		case GameStateEnum::PLAY:
			while (!interfaceElements.empty()) interfaceElements.pop_back();
			appendDrawable(std::make_shared<Button>(sf::Vector2f(1740, 40), sf::Vector2f(160, 50), buttonBlueprints::MAIN_STYLE_BUTTON,
				"Save ", CallbacksEnum::TEST_FN, shared_from_this()));
			appendDrawable(std::make_shared<Button>(sf::Vector2f(1740, 120), sf::Vector2f(160, 50), buttonBlueprints::MAIN_STYLE_BUTTON,
				"Menu ", CallbacksEnum::DISPLAY_MENU, shared_from_this()));
			appendDrawable(std::make_shared<Button>(sf::Vector2f(1740, 200), sf::Vector2f(160, 50), buttonBlueprints::MAIN_STYLE_BUTTON,
				"Exit", CallbacksEnum::SHUT_DOWN, shared_from_this()));
			appendDrawable(std::make_shared<Card>(textures["ct"], shared_from_this()));
			break;

		default: break;
	}
}
