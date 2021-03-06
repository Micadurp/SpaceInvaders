#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include "Object.hpp"
#include"Player.hpp"
#include"Enemy.hpp"
#include"Bullet.hpp"
#include"Wall.hpp"
#include"Score.hpp"
#include<vector>
#include<array>

class Game
{
private:
	Player player;
	std::vector<Enemy> enemies;
	std::array<Bullet, 200> bullets;
	std::vector<Wall> walls;
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
	void Draw(sf::RenderWindow * window);
	bool PlaceWall(int startPosX, int startPosY);
	bool CreatePlayer(int startPosX, int startPosY);
	bool CreateEnemy(int startPosX, int startPosY);
	void InputCheck(const float &frameTime);
	void BulletCheck();
	size_t GetTotalEnemies();
	size_t GetTotalWalls();
	size_t GetTotalBullets();

private:
	bool CheckCollision(Object& object1, Object& object2);
	void aiMove(const sf::Time &frameTime);
	void playerFire();
	void enemyFire();
	void FinishGameCheck(sf::RenderWindow * window, const sf::Time &frameTime);
};

#endif
