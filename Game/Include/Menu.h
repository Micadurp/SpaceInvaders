#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include<vector>

class Menu
{
private:
	sf::Font * font;
	std::vector<sf::Text*> texts;

	bool keyPressed;

	int prevSelection;
	int selection;

public:
	Menu();
	~Menu();

	bool Initialize(sf::Font * gameFont);
	int Run(sf::RenderWindow * window);

	bool Menu::inputHandler();
};


#endif