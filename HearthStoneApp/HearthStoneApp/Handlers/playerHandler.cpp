#pragma once
#include "playerHandler.h"

PlayerHandler::PlayerHandler(int _damage, int _health, int _mana) {
	damage = _damage;
	health = _health;
	mana = currentMana = _mana;
	playerName = std::make_shared<std::string>("");
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

void PlayerHandler::dealDamage(int _damageAmount) {
	if (_damageAmount > health) health = 0;
	else health -= _damageAmount;
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

std::shared_ptr<std::string> PlayerHandler::getPointerToName() {
	return playerName;
}

void PlayerHandler::setHealthPoints(int _newValue) {
	health = _newValue;
}