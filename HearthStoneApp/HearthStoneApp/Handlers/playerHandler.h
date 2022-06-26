#pragma once
#ifndef PLAYER_HANDLER
#define PLAYER_HANDLER
#include <SFML/Graphics.hpp>

/** Class resposible for player's handling. */
class PlayerHandler {

	/** Values indicating amount of damage, health, maximum mana and current mana
	* possesed by player. */
	int damage, health, mana, currentMana;	

	/** Pointer to player's name. */
	std::shared_ptr<std::string> playerName;

public:

	/** Main constructor. */
	PlayerHandler(int _damage, int _health, int _mana);

	/** Fucntion consuming mana and returning true if it is possible, else returning false. */
	bool consumeMana(int _amountOfMana);

	/** Function renewing mana to it maximum state. */
	void renewMana();

	/** Function reducing health amount by the damage amount dealt. */
	void dealDamage(int _damageAmount);

	/** Getter for damage amount. */
	int getDamage();

	/** Getter for health amount. */
	int getHealth();

	/** Getter for current mana amount. */
	int getCurrentMana();

	/** Getter for max mana amount. */
	int getMaxMana();

	/** Function setting health amount. */
	void setHealthPoints(int _newValue);

	/** Getter for pointer to player's name. */
	std::shared_ptr<std::string> getPointerToName();

};
#endif