#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include"Player.h"
#include"Enemy.h"
#include"Bullet.h"
#include"Wall.h"
#include"Score.h"
#include<vector>

class Game
{
private:
	Player * player;
	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;
	std::vector<Wall*> walls;
	bool enemyDirection;
	bool enemyDescent;
	float boundaryCompensation;
	Score * scoreHandler;
	bool finished;
	bool victory;

public:
	Game();
	virtual ~Game();

	bool Initialize(Score * score);
	bool Destroy();
	int RenderGame(sf::RenderWindow * window, const sf::Time &frameTime);

private:
	bool defaultSetup();
	void InputCheck(const sf::Time &frameTime);
	bool BulletCollision(Bullet * bullet, Object * object);
	void aiMove(const sf::Time &frameTime);
	bool PlaceWall(int startPosX, int startPosY);
	void enemyFire();
	void FinishGameCheck(sf::RenderWindow * window, const sf::Time &frameTime);
};

#endif
