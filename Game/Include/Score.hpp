#ifndef SCORE_H
#define SCORE_H

#include <SFML/Graphics.hpp>
#include <fstream>

using namespace std;

class Score
{
private:
	struct PlayerScore
	{
		string name;
		long highScore;
	};

	long totalScore;
	long highScore;
	sf::Text scoreText;
	sf::Text highScoreText;
	std::vector<sf::Text*> topScoresText;
	std::vector<PlayerScore> topHighScores;
	sf::Font * font;

	std::vector<char> playerName;
	std::vector<sf::Text> playerNameText;
	int currKey;
	bool keyPressed;
	bool keyStillPressed;

public:
	Score();
	virtual ~Score();

	bool Initialize(sf::Font * gameFont);
	bool Shutdown();
	bool Run(sf::RenderWindow * window);

	void ChangeScore(long points);

	sf::Text GetTotalScore();
	sf::Text GetHighScore();

	void LoadScore();
	void SaveScore();

	bool winScore(sf::RenderWindow * window);
	bool loseScore(sf::RenderWindow * window);

	bool newHighScore();

};

#endif