#pragma once
#ifndef UPDATABLE_BAR
#define UPDATABLE_BAR
#include <SFML/Graphics.hpp>
#include "updateableRect.h"

enum class BarType {HORIZONTAL, VERTICAL};

class UpdatableBar : public UpdatableRect {

	sf::RectangleShape filling;

	int maxValue, currentValue;

	BarType type;

protected:

	void changeValue(int _newValue);

public:

	UpdatableBar(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, sf::Color _color2, int _maxValue, BarType _type, std::shared_ptr<GameHandler> _gameHandler);

	//Overwritten function from abstact updatable class
	void update();

	bool shouldBeDestroyed();

};
#endif