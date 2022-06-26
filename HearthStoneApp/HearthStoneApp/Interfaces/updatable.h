#pragma once
#ifndef UPDATABLE
#define UPDATABLE
#include <SFML/Graphics.hpp>

/** Interface used by game handler class to managing GUI elements */
class Updatable {

public:

	/** Abstract update function used further in game handler */
	virtual void update() = 0;

	/** Abstract logic indicator function used further in game handler */
	virtual bool shouldBeDestroyed() = 0;

};
#endif