#ifndef BUTTON_H
#define BUTTON_H
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>

class Button
{
	sf::Text text;
	sf::Font font;
	bool focus;
	unsigned int Size;
public:
	Button(sf::String t, sf::Vector2f pos, unsigned int size = 50);
	Button(sf::String t, float pos_x, float pos_y, unsigned int size = 50);
	Button(sf::Image im, float pos_x, float pos_y);
	sf::FloatRect getGlobalBounds();
	~Button(){}
	void render(sf::RenderWindow &window);
	void setFocus(bool foc = true);
};



#endif // BUTTON_H