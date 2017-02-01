#include "Score.h"

Score::Score()
{
}

Score::~Score()
{
	Shutdown();
}

bool Score::Shutdown()
{
	while (topScoresText.size()>0)
	{
		delete topScoresText.back();
		topScoresText.pop_back();
	}
	return true;
}

bool Score::Initialize(sf::Font * gameFont)
{
	font = gameFont;
	totalScore = 0;
	highScore = 0;
	scoreText.setFont(*font);
	scoreText.setColor(sf::Color::Green);
	highScoreText.setFont(*font);
	highScoreText.setColor(sf::Color::Green);
	highScoreText.setPosition(sf::Vector2f(700, 0));

	for (int i = 0; i < 3; ++i)
	{
		playerNameText.push_back(sf::Text());
		playerNameText.back().setFont(*font);
		playerNameText.back().setColor(sf::Color::White);
		playerNameText.back().setString("AAA");
		playerNameText.back().setPosition(sf::Vector2f(300 + (20 * i), 250));
	}
	playerNameText.front().setColor(sf::Color::Yellow);

	topScoresText.push_back(new sf::Text());
	topScoresText.back()->setFont(*font);
	topScoresText.back()->setColor(sf::Color::Green);
	topScoresText.back()->setString("Sum");
	topScoresText.back()->setPosition(sf::Vector2f(300, 250));
	topScoresText.push_back(new sf::Text());
	topScoresText.back()->setFont(*font);
	topScoresText.back()->setColor(sf::Color::Green);
	topScoresText.back()->setPosition(sf::Vector2f(300, 300));
	topScoresText.back()->setString("Ting");
	topScoresText.push_back(new sf::Text());
	topScoresText.back()->setFont(*font);
	topScoresText.back()->setColor(sf::Color::Green);
	topScoresText.back()->setPosition(sf::Vector2f(300, 350));
	topScoresText.back()->setString("Wong");

	playerName.push_back('A');
	playerName.push_back('A');
	playerName.push_back('A');
	currKey = 0;

	LoadScore();

	keyPressed = false;
	keyStillPressed = false;

	return true;
}

bool Score::Run(sf::RenderWindow * window)
{
	for each (sf::Text * text in topScoresText)
	{
		window->draw(*text);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		return false;
	}

	return true;
}

void Score::ChangeScore(long points)
{
	totalScore += points;
	if (totalScore > highScore)
	{
		highScore = totalScore;
	}
}


sf::Text Score::GetTotalScore()
{
	scoreText.setString(std::to_string(totalScore));
	return scoreText;
}

sf::Text Score::GetHighScore()
{
	highScoreText.setString(std::to_string(highScore));
	return highScoreText;
}

void Score::LoadScore()
{
	int counter = 0;
	string tempString = "";
	long tempLong = 0L;
	ifstream myfile;
	myfile.open("score.txt");
	while (counter<3)
	{
		topHighScores.push_back(PlayerScore());
		myfile >> topHighScores.back().name;
		myfile >> topHighScores.back().highScore;
		topScoresText.at(counter)->setString(topHighScores.back().name + ": " + std::to_string(topHighScores.back().highScore));
		counter++;
	}
	highScore = topHighScores.front().highScore;
	myfile.close();
}

void Score::SaveScore()
{
	ofstream myfile;
	myfile.open("score.txt", std::ofstream::out | std::ofstream::trunc);
	for each (PlayerScore scores in topHighScores)
	{
		myfile << scores.name << endl;
		myfile << scores.highScore << endl;
	}
	myfile.close();
}

bool Score::winScore(sf::RenderWindow * window)
{
	sf::Text winScreen = sf::Text("Victory", *font);
	winScreen.setColor(sf::Color::Green);
	winScreen.setPosition(sf::Vector2f(300, 200));

	window->draw(GetTotalScore());
	window->draw(GetHighScore());
	window->draw(winScreen);

	if (topHighScores.at(2).highScore < totalScore)
	{
		for (int i = 0; i < playerNameText.size(); ++i)
		{
			playerNameText.at(i).setString(playerName.at(i));
			window->draw(playerNameText.at(i));
		}
		newHighScore();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		bool newScore = false;
		PlayerScore tempScore;
		PlayerScore tempScore2;
		for (int i = 0; i < topHighScores.size(); ++i)
		{
			if (newScore && i != topHighScores.size())
			{
				tempScore2 = topHighScores.at(i);
				topHighScores.at(i) = tempScore;
				tempScore = tempScore2;
			}
			else if (topHighScores.at(i).highScore < totalScore && !newScore)
			{
				newScore = true;
				tempScore = topHighScores.at(i);
				topHighScores.at(i).highScore = totalScore;
				topHighScores.at(i).name = string() + playerName.at(0) + playerName.at(1) + playerName.at(2);
			}
			topScoresText.at(i)->setString(topHighScores.at(i).name + ": " + std::to_string(topHighScores.at(i).highScore));
		}

		totalScore = 0;
		return true;
	}
	return false;
}

bool Score::loseScore(sf::RenderWindow * window)
{
	sf::Text loseScreen = sf::Text("You lose", *font);
	loseScreen.setColor(sf::Color::Red);
	loseScreen.setPosition(sf::Vector2f(300, 200));

	window->draw(GetTotalScore());
	window->draw(GetHighScore());
	window->draw(loseScreen);

	if (topHighScores.at(2).highScore < totalScore)
	{
		for (int i = 0; i < playerNameText.size(); ++i)
		{
			playerNameText.at(i).setString(playerName.at(i));
			window->draw(playerNameText.at(i));
		}
		newHighScore();
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		bool newScore = false;
		PlayerScore tempScore;
		PlayerScore tempScore2;
		for (int i = 0; i < topHighScores.size(); ++i)
		{
			if (newScore && i != topHighScores.size())
			{
				tempScore2 = topHighScores.at(i);
				topHighScores.at(i) = tempScore;
				tempScore = tempScore2;
			}
			else if (topHighScores.at(i).highScore < totalScore && !newScore)
			{
				newScore = true;
				tempScore = topHighScores.at(i);
				topHighScores.at(i).highScore = totalScore;
				topHighScores.at(i).name = string() + playerName.at(0) + playerName.at(1) + playerName.at(2);
			}
			topScoresText.at(i)->setString(topHighScores.at(i).name + ": " + std::to_string(topHighScores.at(i).highScore));
		}

		totalScore = 0;
		return true;
	}
	return false;
}


bool Score::newHighScore()
{
	keyPressed = false;
	if (!keyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (!keyStillPressed)
			{
				playerNameText.at(currKey).setColor(sf::Color::White);

				if (currKey == 0)
				{
					currKey = 2;
				}
				else
				{
					currKey--;
				}
				playerNameText.at(currKey).setColor(sf::Color::Yellow);
			}
			keyPressed = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (!keyStillPressed)
			{
				playerNameText.at(currKey).setColor(sf::Color::White);
				if (currKey == 2)
				{
					currKey = 0;
				}
				else
				{
					currKey++;
				}
				playerNameText.at(currKey).setColor(sf::Color::Yellow);
			}
			keyPressed = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{

			if (!keyStillPressed)
			{
				if (playerName.at(currKey) == 'Z')
				{
					playerName.at(currKey) = 'A';
				}
				else
				{
					playerName.at(currKey)++;
				}
			}
			keyPressed = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			if (!keyStillPressed)
			{
				if (playerName.at(currKey) == 'A')
				{
					playerName.at(currKey) = 'Z';
				}
				else
				{
					playerName.at(currKey)--;
				}
			}
			keyPressed = true;
		}
	}

	keyStillPressed = keyPressed;

	return true;
}