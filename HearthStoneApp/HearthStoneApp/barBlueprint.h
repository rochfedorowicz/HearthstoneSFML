#pragma once
#ifndef BAR_BLUEPRINT
#define BAR_BLUEPRINT
#include <SFML/Graphics.hpp>
#include <functional>
#include "getValueFunctions.h"

class BarBlueprint {

public:

	sf::Color backgroundColor;

	sf::Color fillingColor;

	std::shared_ptr<std::function<int(std::shared_ptr<GameHandler>)>> funcntionPtr;

	std::shared_ptr<std::function<int(std::shared_ptr<GameHandler>)>> funcntionPtr2;

	BarBlueprint(sf::Color _backGroundColor, sf::Color _fillingColor,
		std::shared_ptr<std::function<int(std::shared_ptr<GameHandler>)>> _funcntionPtr,
		std::shared_ptr<std::function<int(std::shared_ptr<GameHandler>)>> _funcntionPtr2);

	int getMaxValue(std::shared_ptr<GameHandler> _gameHandler);
};


namespace barBlueprints {

	const BarBlueprint PLAYERS_MANA_BAR = BarBlueprint(sf::Color::Black, sf::Color::Blue,
		std::make_shared<std::function<int(std::shared_ptr<GameHandler>)>>(&getValueFunctions::getValueByPlayersMana),
		std::make_shared<std::function<int(std::shared_ptr<GameHandler>)>>(&getValueFunctions::getMaxValueByPlayersMana));

	const BarBlueprint ROUNDS_TIMER_BAR = BarBlueprint(sf::Color::Black, sf::Color::Green,
		std::make_shared<std::function<int(std::shared_ptr<GameHandler>)>>(&getValueFunctions::getValueByRoundsTimer),
		std::make_shared<std::function<int(std::shared_ptr<GameHandler>)>>(&getValueFunctions::getMaxValueByRoundsTimer));
}
#endif