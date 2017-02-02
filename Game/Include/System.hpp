#ifndef SYSTEM_H
#define SYSTEM_H

#include <SFML/Graphics.hpp>
#include"Game.hpp"
#include"Menu.hpp"
#include"Score.hpp"

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
	virtual ~System();

	bool Initialize();
	bool Shutdown();
	bool Run();



};


#endif