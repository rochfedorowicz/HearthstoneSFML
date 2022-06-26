#pragma once
#ifndef BUTTON_BLUEPRINT
#define BUTTON_BLUEPRINT
#include <SFML/Graphics.hpp>
#include <functional>
#include "callbacks.h"
#include "colorBlueprint.h"

/** Button blueprint used for easier button constructor calls,
* it's predefined set of atributes representing typical buttons. */
class ButtonBlueprint {
	
public:

	/** Name displayed at the button. */
	std::string displayedName;

	/** Color of button. */
	sf::Color color;

	/** Font's name. */
	std::string fontName;

	/** Font's color. */
	sf::Color fontColor;

	/** Pointer to callback function used by button. */
	std::shared_ptr<std::function<void(std::shared_ptr<GameHandler>)>> callbackFunction;

	/** Main buttons blueprint's constructor. */
	ButtonBlueprint(std::string _name, sf::Color _color, std::string _fontName, sf::Color _fontColor, 
		std::shared_ptr<std::function<void(std::shared_ptr<GameHandler>)>> _callbackFunction);

};

/** All predefined button blueprints */
namespace buttonBlueprints {

	/** Testing button - all it can do is printing "1" into console. */
	const ButtonBlueprint TEST_BUTTON = ButtonBlueprint("Test", colorBlueprints::BUTTON_BEIGE, "Matura",
		sf::Color::Black, std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::testFn));

	/** Button that is able to shut down current window. */
	const ButtonBlueprint SHUT_DOWN_BUTTON = ButtonBlueprint("Exit", colorBlueprints::BUTTON_BEIGE, "Matura",
		sf::Color::Black, std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::shutDown));

	/** Button playing game. */
	const ButtonBlueprint PLAY_GAME_BUTTON = ButtonBlueprint("Play", colorBlueprints::BUTTON_BEIGE, "Matura",
		sf::Color::Black, std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::playGame));

	/** Button displaying setting menu. */
	const ButtonBlueprint DISPLAY_SETTINGS_BUTTON = ButtonBlueprint("Settings", colorBlueprints::BUTTON_BEIGE, "Matura",
		sf::Color::Black, std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::displaySettings));

	/** Button displaying main menu. */
	const ButtonBlueprint DISPLAY_MENU_BUTTON = ButtonBlueprint("Menu", colorBlueprints::BUTTON_BEIGE, "Matura",
		sf::Color::Black, std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::displayMenu));

	/** Buton changing resolution to 1920 x 1080. */
	const ButtonBlueprint CHANGE_RESOLUTION_TO_1920_X_1080_BUTTON = ButtonBlueprint("Change resolution to 1920x1080",
		colorBlueprints::BUTTON_BEIGE, "Matura", sf::Color::Black,
		std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::changeResolutionTo1920x1080));

	/** Button chaning resolution to 1280 x 720. */
	const ButtonBlueprint CHANGE_RESOLUTION_TO_1280_X_720_BUTTON = ButtonBlueprint("Change resolution to 1280x720",
		colorBlueprints::BUTTON_BEIGE, "Matura", sf::Color::Black,
		std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::changeResolutionTo1280x720));

	/** Button skiping round. */
	const ButtonBlueprint SKIP_ROUND_BUTTON = ButtonBlueprint("Skip round",
		colorBlueprints::BUTTON_BEIGE, "Matura", sf::Color::Black,
		std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::skipRound));

	/** Button that display name input's menu window. */
	const ButtonBlueprint PREPARE_GAMEPLAY_BUTTON = ButtonBlueprint("Start",
		colorBlueprints::BUTTON_BEIGE, "Matura", sf::Color::Black,
		std::make_shared<std::function<void(std::shared_ptr<GameHandler>)>>(&callbacks::proceedToGamePlay));
}
#endif