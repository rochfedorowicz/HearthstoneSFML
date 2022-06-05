#include "barBlueprint.h"

BarBlueprint::BarBlueprint(sf::Color _backGroundColor, sf::Color _fillingColor,
	std::shared_ptr<std::function<int(std::shared_ptr<GameHandler>)>>_funcntionPtr,
	std::shared_ptr<std::function<int(std::shared_ptr<GameHandler>)>> _funcntionPtr2) {
	backgroundColor = _backGroundColor;
	fillingColor = _fillingColor;
	funcntionPtr = _funcntionPtr;
	funcntionPtr2 = _funcntionPtr2;
}

int BarBlueprint::getMaxValue(std::shared_ptr<GameHandler> _gameHandler) {
	return funcntionPtr2->operator()(_gameHandler);
}