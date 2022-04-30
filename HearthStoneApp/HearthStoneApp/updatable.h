#pragma once
#ifndef UPDATABLE
#define UPDATABLE
#include <SFML/Graphics.hpp>

class Updatable : public sf::Drawable {

protected:

	//Overwritten function from abstact drawable class
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

public:

	//Virtual function that updates state of object
	virtual void update() = 0;

};
#endif