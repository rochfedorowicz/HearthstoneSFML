#pragma once
#include "updateableBar.h"

UpdatableBar::UpdatableBar(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, sf::Color _color2,
	int _maxValue, BarType _type, std::shared_ptr<std::function<int(std::shared_ptr<GameHandler>)>> _funcntionPtr, std::shared_ptr<GameHandler> _gameHandler)
	: UpdatableRect(_position, _size, _color, _gameHandler) {
	filling = sf::RectangleShape(_size);
	filling.setPosition(_position);
	filling.setFillColor(_color2);
	maxValue = currentValue = _maxValue;
	type = _type;
	funcntionPtr = _funcntionPtr;
}

UpdatableBar::UpdatableBar(sf::Vector2f _position, sf::Vector2f _size, BarType _type, BarBlueprint _barBluePrint, std::shared_ptr<GameHandler> _gameHandler) 
	: UpdatableRect(_position, _size, _barBluePrint.backgroundColor, _gameHandler) {
	filling = sf::RectangleShape(_size);
	filling.setPosition(_position);
	filling.setFillColor(_barBluePrint.fillingColor);
	maxValue = currentValue = _barBluePrint.getMaxValue(_gameHandler);
	type = _type;
	funcntionPtr = _barBluePrint.funcntionPtr;
}


void UpdatableBar::update() {
	UpdatableRect::update();
	gameHandler->getWindowPtr()->draw(filling);
	changeValue(funcntionPtr->operator()(gameHandler));
}

bool UpdatableBar::shouldBeDestroyed() {
	return false;
}

void UpdatableBar::changeValue(int _newValue) {
	currentValue = _newValue;
	if (type == BarType::HORIZONTAL)
		filling.setSize(sf::Vector2f(_newValue * 1.0f / maxValue * body.getSize().x, filling.getSize().y));
	if (type == BarType::VERTICAL) {
		filling.setSize(sf::Vector2f(filling.getSize().x, _newValue * 1.0f / maxValue * body.getSize().y));
		filling.setPosition(body.getPosition() + sf::Vector2f(0, (1.0f - _newValue * 1.0f / maxValue) * body.getSize().y));
	}
}