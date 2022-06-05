#pragma once
#include "playerHandler.h"

PlayerHandler::PlayerHandler(int _damage, int _health, int _mana) {
	damage = _damage;
	health = _health;
	mana = currentMana = _mana;
}

bool PlayerHandler::consumeMana(int _amountOfMana) {
	if (currentMana - _amountOfMana >= 0) {
		currentMana -= _amountOfMana;
		return true;
	}
	else return false;
}

void PlayerHandler::renewMana() {
	currentMana = mana;
}

int PlayerHandler::getDamage() {
	return damage;
}

int PlayerHandler::getHealth() {
	return health;
}

int PlayerHandler::getCurrentMana() {
	return currentMana;
}

int PlayerHandler::getMaxMana() {
	return mana;
}