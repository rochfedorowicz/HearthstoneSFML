#pragma once
#ifndef PLAYER_HANDLER
#define PLAYER_HANDLER
#include <SFML/Graphics.hpp>

class PlayerHandler {

	int damage, health, mana, currentMana;	

	std::shared_ptr<std::string> playerName;

public:

	PlayerHandler(int _damage, int _health, int _mana);

	bool consumeMana(int _amountOfMana);

	void renewMana();

	int getDamage();

	int getHealth();

	int getCurrentMana();

	int getMaxMana();

	std::shared_ptr<std::string> getPointerToName();

};
#endif