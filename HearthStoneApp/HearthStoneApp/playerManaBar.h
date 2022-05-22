#pragma once
#ifndef PLAYER_MANA_BAR
#define PLAYER_MANA_BAR
#include <SFML/Graphics.hpp>
#include "updateableBar.h"

class PlayerManaBar : public UpdatableBar {

public:

	PlayerManaBar(sf::Vector2f _position, sf::Vector2f _size, BarType _type, std::shared_ptr<GameHandler> _gameHandler);

	//Overwritten function from abstact updatable class
	void update();

	bool shouldBeDestroyed();

};
#endif