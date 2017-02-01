#include "Menu.h"


Menu::Menu()
{

}

Menu::~Menu()
{
	while (texts.size()>0)
	{
		delete texts.back();
		texts.pop_back();
	}
}

bool Menu::Initialize(sf::Font * gameFont)
{
	font = gameFont;
	texts.push_back(new sf::Text());
	texts.back()->setFont(*font);
	texts.back()->setColor(sf::Color::Yellow);
	texts.back()->setString("Start Game");
	texts.back()->setPosition(sf::Vector2f(300, 250));

	texts.push_back(new sf::Text());
	texts.back()->setFont(*font);
	texts.back()->setColor(sf::Color::White);
	texts.back()->setString("High Score");
	texts.back()->setPosition(sf::Vector2f(300, 300));

	texts.push_back(new sf::Text());
	texts.back()->setFont(*font);
	texts.back()->setColor(sf::Color::White);
	texts.back()->setString("Quit");
	texts.back()->setPosition(sf::Vector2f(300, 350));

	keyPressed = false;

	prevSelection = 0;
	selection = 0;
	return true;
}

int Menu::Run(sf::RenderWindow * window)
{
	if (!inputHandler())
	{
		return (selection + 1);
	}

	if (prevSelection != selection)
	{
		texts.at(selection)->setColor(sf::Color::Yellow);
		texts.at(prevSelection)->setColor(sf::Color::White);
		prevSelection = selection;
	}

	for each (sf::Text * text in texts)
	{
		window->draw(*text);
	}

	return 0;
}

bool Menu::inputHandler()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (!keyPressed)
		{
			if (selection == 0)
			{
				selection = 2;
			}
			else
			{
				selection--;
			}
		}
		keyPressed = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (!keyPressed)
		{
			selection++;
			selection = selection % 3;
			keyPressed = true;
		}
	}
	else
	{
		keyPressed = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		return false;
	}
	return true;
}