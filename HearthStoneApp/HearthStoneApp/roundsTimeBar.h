#pragma once
#ifndef ROUND_TIME_BAR
#define ROUND_TIME_BAR
#include <SFML/Graphics.hpp>
#include "updateableBar.h"

class RoundsTimeBar : public UpdatableBar {

public:

	RoundsTimeBar(sf::Vector2f _position, sf::Vector2f _size, BarType _type, std::shared_ptr<GameHandler> _gameHandler);

	//Overwritten function from abstact updatable class
	void update();

	bool shouldBeDestroyed();

};
#endif