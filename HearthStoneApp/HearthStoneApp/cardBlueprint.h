#pragma once
#ifndef CARD_BLUEPRINT
#define CARD_BLUEPRINT
#include <string>

/** Class gathering some card's parameters in one place. */
class CardBlueprint {

public:

	/** Texture's name. */
	std::string textureName;

	/** Amount of statistics possesed by card. */
	int health, damage, mana;

	/** Main constructor. */
	CardBlueprint(std::string _textureName, int _health, int _damage, int _mana);

};

/** All predefined button blueprints.3 */
namespace cardBlueprints {

	/** Orc card has the best health number, but the wrost damage number. */
	const CardBlueprint ORC = CardBlueprint("orcCard", 20, 5, 3);

	/** Wiking card has intermediate health and damage number. */
	const CardBlueprint WIKING = CardBlueprint("wikingCard", 12, 7, 4);
	
	/** Warrior card has the highest damage number but the worst health number. */
	const CardBlueprint WARRIOR = CardBlueprint("warriorCard", 8, 9, 5);

}
#endif