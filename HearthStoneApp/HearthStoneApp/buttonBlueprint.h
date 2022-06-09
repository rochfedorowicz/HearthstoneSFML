#pragma once
#ifndef BUTTON_BLUEPRINT
#define BUTTON_BLUEPRINT
#include <SFML/Graphics.hpp>
#include <functional>
#include "callbacks.h"
#include "colorBlueprint.h"

//Button blueprint used for easier button constructor calls,
//it's predefined set of atributes representing typical buttons
class ButtonBlueprint {
	
public:

	std::string displayedName;

	//Color of button set in blue print
	sf::Color color;

	//Font's name set in blue print
	std::string fontName;

	//Font's color set in blue print
	sf::Color fontColor;

	std::shared_ptr<std::function<void(std::shared_ptr<GameHandler>)>> callbackFunction;

	

	//Deafult button's blueprint constructor
	ButtonBlueprint(std::string _name, sf::Color _color, std::string _fontName, sf::Color _fontColor, 
		std::shared_ptr<std::function<void(std::shared_ptr<GameHandler>)>> _callbackFunction);

};

//All predefined button blueprints
namespace buttonBlueprints {

	const ButtonBlueprint TEST_BUTTON = ButtonBlueprint("Test", colorBlueprints::BUTTON_BEIGE, "Matura",
		sf::Color::Black, std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::testFn));

	const ButtonBlueprint SHUT_DOWN_BUTTON = ButtonBlueprint("Exit", colorBlueprints::BUTTON_BEIGE, "Matura",
		sf::Color::Black, std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::shutDown));

	const ButtonBlueprint PLAY_GAME_BUTTON = ButtonBlueprint("Play", colorBlueprints::BUTTON_BEIGE, "Matura",
		sf::Color::Black, std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::playGame));

	const ButtonBlueprint DISPLAY_SETTINGS_BUTTON = ButtonBlueprint("Settings", colorBlueprints::BUTTON_BEIGE, "Matura",
		sf::Color::Black, std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::displaySettings));

	const ButtonBlueprint DISPLAY_MENU_BUTTON = ButtonBlueprint("Menu", colorBlueprints::BUTTON_BEIGE, "Matura",
		sf::Color::Black, std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::displayMenu));

	const ButtonBlueprint CHANGE_RESOLUTION_TO_1920_X_1080_BUTTON = ButtonBlueprint("Change resolution to 1920x1080",
		colorBlueprints::BUTTON_BEIGE, "Matura", sf::Color::Black,
		std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::changeResolutionTo1920x1080));

	const ButtonBlueprint CHANGE_RESOLUTION_TO_1280_X_720_BUTTON = ButtonBlueprint("Change resolution to 1280x720",
		colorBlueprints::BUTTON_BEIGE, "Matura", sf::Color::Black,
		std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::changeResolutionTo1280x720));
}
#endif