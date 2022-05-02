#pragma once
#ifndef BUTTON_BLUEPRINT
#define BUTTON_BLUEPRINT
#include <SFML/Graphics.hpp>

//Button blueprint used for easier button constructor calls,
//it's predefined set of atributes representing particular style
class ButtonBlueprint {

public:
	
	//Color of button set in blue print
	sf::Color color;

	//Font's name set in blue print
	std::string fontName;

	//Font's color set in blue print
	sf::Color fontColor;

	//Deafult button's blueprint constructor
	ButtonBlueprint(sf::Color _color, std::string _fontName, sf::Color _fontColor);
};

//All predefined button blueprints
namespace buttonBlueprints {

	//Deafult button style
	const ButtonBlueprint DEFAULT_BUTTON = ButtonBlueprint(sf::Color::White, "Calibri", sf::Color::Black);

	//Main game's style button
	const ButtonBlueprint MAIN_STYLE_BUTTON = ButtonBlueprint(sf::Color(225, 186, 102), "Matura", sf::Color::Black);
}
#endif