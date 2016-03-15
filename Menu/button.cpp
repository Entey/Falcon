#include "Button.h"

Button::Button(sf::String t, sf::Vector2f pos, unsigned int size)
{
	Size = size;
	font.loadFromFile("images/GN.ttf");
	text = sf::Text(t, font, Size);
	text.setPosition(pos);
	focus = false;
}

Button::Button(sf::String t, float pos_x, float pos_y, unsigned int size)
{
	Size = size;
	font.loadFromFile("images/GN.ttf");
	text = sf::Text(t, font, Size);
	text.setPosition(sf::Vector2f(pos_x, pos_y));
	focus = false;
}

void Button::render(sf::RenderWindow &window)
{
	if (focus)
	{
		text.setCharacterSize(Size + 2);
		text.setColor(sf::Color::Green);
		text.setRotation(-5.0);
	}
	else
	{
		text.setCharacterSize(Size);
		text.setColor(sf::Color::White);
		text.setRotation(0.0);
	}
	window.draw(text);
}

void Button::setFocus(bool foc){
	focus = foc;
}

sf::FloatRect Button::getGlobalBounds()
{
	return text.getGlobalBounds();
}