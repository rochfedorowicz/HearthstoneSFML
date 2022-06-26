#pragma once
#ifndef COLOR_BLUEPRINT
#define COLOR_BLUEPRINT
#include <SFML/Graphics.hpp>

/** All predefined colors. */
namespace colorBlueprints {

	/** Color used for mainly for player's mana. */
	const sf::Color LIGHT_BLUE = sf::Color(6, 133, 255);

	/** Color used mainly for opponent's mana. */
	const sf::Color DARK_BLUE = sf::Color(28, 21, 239);

	/** Color used mainly for buttons. */
	const sf::Color BUTTON_BEIGE = sf::Color(225, 186, 102);

	/** Colors used mainly for backfround. */
	const sf::Color BACKGROUND_BROWN = sf::Color(149, 69, 53);

}
#endif