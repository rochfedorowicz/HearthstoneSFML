#pragma once
#ifndef BAR_BLUEPRINT
#define BAR_BLUEPRINT
#include <SFML/Graphics.hpp>
#include <functional>
#include "getValueFunctions.h"
#include "colorBlueprint.h"

/** Class being a predefined set of parameters for bars. */
class BarBlueprint {

public:

	/** Bar's background color. */
	sf::Color backgroundColor;

	/** Bar's filling color. */
	sf::Color fillingColor;

	/** Pointer to function that is used to update state of bar. */
	std::shared_ptr<std::function<int(std::shared_ptr<GameHandler>)>> funcntionPtr;

	/** Pointer to function that is used to get maximum value in bar. */
	std::shared_ptr<std::function<int(std::shared_ptr<GameHandler>)>> funcntionPtr2;

	/** Main bar blueprint's construtor. */
	BarBlueprint(sf::Color _backGroundColor, sf::Color _fillingColor,
		std::shared_ptr<std::function<int(std::shared_ptr<GameHandler>)>> _funcntionPtr,
		std::shared_ptr<std::function<int(std::shared_ptr<GameHandler>)>> _funcntionPtr2);

	/** Function using second function pointer to provide maximum value for created bar. */
	int getMaxValue(std::shared_ptr<GameHandler> _gameHandler);
};

/** All predefined bars. */
namespace barBlueprints {

	/** Bar tha display's mana of player. Synchronized with player's handler. */
	const BarBlueprint PLAYERS_MANA_BAR = BarBlueprint(sf::Color::Black, colorBlueprints::LIGHT_BLUE,
		std::make_shared<std::function<int(std::shared_ptr<GameHandler>)>>(&getValueFunctions::getValueByPlayersMana),
		std::make_shared<std::function<int(std::shared_ptr<GameHandler>)>>(&getValueFunctions::getMaxValueByPlayersMana));

	/** Bar tha display's mana of opponent. Synchronized with players's handler. */
	const BarBlueprint OPPONENTS_MANA_BAR = BarBlueprint(sf::Color::Black, colorBlueprints::DARK_BLUE,
		std::make_shared<std::function<int(std::shared_ptr<GameHandler>)>>(&getValueFunctions::getValueByOpponentsMana),
		std::make_shared<std::function<int(std::shared_ptr<GameHandler>)>>(&getValueFunctions::getMaxValueByOpponentsMana));

	/** Bar tha display's current amount of time in a round. Synchronized with round's handler. */
	const BarBlueprint ROUNDS_TIMER_BAR = BarBlueprint(sf::Color::Black, sf::Color::Green,
		std::make_shared<std::function<int(std::shared_ptr<GameHandler>)>>(&getValueFunctions::getValueByRoundsTimer),
		std::make_shared<std::function<int(std::shared_ptr<GameHandler>)>>(&getValueFunctions::getMaxValueByRoundsTimer));
}
#endif