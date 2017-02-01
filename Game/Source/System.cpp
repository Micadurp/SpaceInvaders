#include "System.h"

System::System()
{
	window = nullptr;
	score = nullptr;
	font = nullptr;
}

System::~System()
{
	if (window)
	{
		delete window;
		window = 0;
	}

	if (score)
	{
		delete score;
		score = 0;
	}

	if (font)
	{
		delete font;
		font = 0;
	}
}

bool System::Initialize()
{
	state = 0;
	srand(time(NULL));
	clock.restart();
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "Space Invaders!");


	font = new sf::Font();
	if (!font->loadFromFile("CFRobertNelson-Regular.ttf"))
	{
		return false;
	}

	if (!menu.Initialize(font))
	{
		return false;
	}

	score = new Score();
	if (!score->Initialize(font))
	{
		return false;
	}

	if (!game.Initialize(score))
	{
		return false;
	}


	return true;
}

bool System::Run()
{
	while (window->isOpen())
	{
		frameTime = clock.getElapsedTime();
		clock.restart();

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
			}
		}

		window->clear();

		if (state == 0)
		{
			state = menu.Run(window);
			if (state == 1)
			{
				game.Destroy();
				game.Initialize(score);
			}
		}
		else if (state == 1)
		{
			if (game.RenderGame(window, frameTime) == 1)
			{
				state = 2;
			}
		}
		else if (state == 2)
		{
			if (!score->Run(window))
			{
				state = 0;
			}
		}
		else if (state == 3)
		{
			window->close();
		}

		window->display();
	}

	return true;
}
