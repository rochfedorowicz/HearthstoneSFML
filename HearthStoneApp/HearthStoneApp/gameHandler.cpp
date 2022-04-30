#pragma once
#include "gameHandler.h"

GameHandler::GameHandler() {
	currentWindowPtr = std::make_shared<sf::RenderWindow>(sf::VideoMode(640, 480), "This app", sf::Style::Titlebar);
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
		for (auto& element : interfaceElements) {
			currentWindowPtr->draw(*element);
			element->update();
		}
        currentWindowPtr->display();
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

		case CallbacksEnum::TEST_FN: callbacksQueue.push(&callbacks::fn); break;

		case CallbacksEnum::SHUT_DOWN: callbacksQueue.push(&callbacks::shutDown); break;

		default: break;
	}
}
