#pragma once
#ifndef CARD_BLUEPRINT
#define CARD_BLUEPRINT
#include <string>

class CardBlueprint {

public:

	std::string textureName;

	int health, damage, mana;

	CardBlueprint(std::string _textureName, int _health, int _damage, int _mana);

};

//All predefined button blueprints
namespace cardBlueprints {

	const CardBlueprint ORC = CardBlueprint("orcCard", 20, 5, 3);
	const CardBlueprint WIKING = CardBlueprint("wikingCard", 12, 7, 4);
	const CardBlueprint WARRIOR = CardBlueprint("warriorCard", 8, 9, 5);
	const CardBlueprint OPONNENT = CardBlueprint("opponentCard", 45, 15, 4);
	const CardBlueprint HERO = CardBlueprint("heroCard", 100, 5, 3);

}
#endif