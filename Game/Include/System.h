#ifndef SYSTEM_H
#define SYSTEM_H

#include <SFML/Graphics.hpp>
#include"Game.h"
#include"Menu.h"
#include"Score.h"

class System
{
private:
	sf::RenderWindow * window;
	sf::Clock clock;
	sf::Time frameTime;

	Game game;
	Menu menu;
	Score * score;

	sf::Font * font;

	int state;

public:
	System();
	~System();

	bool Initialize();
	bool Run();



};


#endif