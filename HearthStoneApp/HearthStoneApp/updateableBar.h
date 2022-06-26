#pragma once
#ifndef UPDATABLE_BAR
#define UPDATABLE_BAR
#include <SFML/Graphics.hpp>
#include "updateableRect.h"
#include "barBlueprint.h"

/** Enum specifiing posible types of bar. */
enum class BarType {HORIZONTAL, VERTICAL};

/** Class representing bar showing some content. */
class UpdatableBar : public UpdatableRect {

	/** Filling rectangle. */
	sf::RectangleShape filling;

	/** Maximum and current value of content. */
	int maxValue, currentValue;

	/** Type of bar. */
	BarType type;

	/** Pointer to updating value function. */
	std::shared_ptr<std::function<int(std::shared_ptr<GameHandler>)>> funcntionPtr;

protected:

	/** Function changing value. */
	void changeValue(int _newValue);

public:

	/** Main constructor. */
	UpdatableBar(sf::Vector2f _position, sf::Vector2f _size, sf::Color _color, sf::Color _color2, int _maxValue,
		BarType _type, std::shared_ptr<std::function<int(std::shared_ptr<GameHandler>)>> _funcntionPtr, std::shared_ptr<GameHandler> _gameHandler);

	/** Updatable bar's constructor that uses predefined set of parameters called blueprint. */
	UpdatableBar(sf::Vector2f _position, sf::Vector2f _size, BarType _type, BarBlueprint _barBluePrint, std::shared_ptr<GameHandler> _gameHandler);

	/** Overwritten function from abstact updatable class. */
	void update();

	/** Overwritten function from abstact updatable class. */
	bool shouldBeDestroyed();

};
#endif