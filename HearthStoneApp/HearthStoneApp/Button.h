#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Button : public sf::Drawable {
	
private:
	sf::RectangleShape body;
	sf::Text text;
	sf::RenderWindow* parentWindow;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

public:
	Button(sf::Vector2f _position, sf::Color _color, std::string _text, sf::RenderWindow *_parentWindow);

};