#include "Game.hpp"

Game::Game()
{
}

Game::~Game()
{
	Destroy();
}

bool Game::Initialize(Score * score)
{
	scoreHandler = score;
	enemyDirection = true;
	finished = false;
	victory = false;
	return true;
}

bool Game::Destroy()
{
	player.Shutdown();

	enemies.clear();
	walls.clear();
	bullets.clear();

	return true;
}

int Game::RenderGame(sf::RenderWindow * window, const sf::Time &frameTime)
{
	FinishGameCheck(window, frameTime);

	if (!finished)
	{
		//InputCheck(frameTime.asSeconds());

		BulletCheck();

		aiMove(frameTime);
		enemyFire();
		for (auto& bullet : bullets)
		{
			if (bullet.IsAlive())
			{
				bullet.Move(100 * frameTime.asSeconds());
			}
		}
		for (auto& enemy : enemies)
		{
			if (enemy.IsAlive())
			{
				if ((enemy.GetPosX() < 0 || enemy.GetPosX() > 800) && !enemyDescent)
				{
					enemyDirection = !enemyDirection;
					enemyDescent = true;

					if (enemy.GetPosX() < 0)
					{
						boundaryCompensation = -enemy.GetPosX();
					}
					else
					{
						boundaryCompensation = 800 - enemy.GetPosX();
					}
				}
			}
		}

		Draw(window);
	}
	else
	{
		if (victory)
		{
			if (scoreHandler->winScore(window))
			{
				scoreHandler->SaveScore();
				return 1;
			}

		}
		else
		{
			if (scoreHandler->loseScore(window))
			{
				scoreHandler->SaveScore();
				return 1;
			}
		}

	}

	return 0;
}
void Game::Draw(sf::RenderWindow * window)
{
	window->draw(*player.GetModel());

	for (auto& bullet : bullets)
	{
		if (bullet.IsAlive())
		{
			window->draw(*bullet.GetModel());
		}
	}
	for (auto& enemy : enemies)
	{
		if (enemy.IsAlive())
		{
			window->draw(*enemy.GetModel());
		}
	}
	for (auto& wall : walls)
	{
		if (wall.IsAlive())
		{
			window->draw(*wall.GetModel());
		}
	}
	window->draw(scoreHandler->GetTotalScore());
	window->draw(scoreHandler->GetHighScore());
}

void Game::InputCheck(const float &frameTime)
{
	if (sf::Event::KeyPressed)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			finished = true;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player.Move(frameTime, true);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player.Move(frameTime, false);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !player.IsShooting())
		{
			playerFire();
		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			player.SetShooting(false);
		}
	}
}

void Game::BulletCheck()
{
	for (auto& bullet : bullets)
	{
		if (bullet.IsAlive())
		{
			if (bullet.GetPosY() < -1)
			{
				bullet.Kill();
				continue;
			}

			if (CheckCollision(bullet, player))
			{
				player.Kill();
			}

			for (auto& enemy : enemies)
			{
				if (enemy.IsAlive())
				{
					if (CheckCollision(bullet, enemy))
					{
						scoreHandler->AddPoints(enemy.GetPoints());
						enemy.Kill();
						bullet.Kill();
						break;
					}
				}
			}

			for (auto& wall : walls)
			{
				if (wall.IsAlive())
				{
					if (CheckCollision(bullet, wall))
					{
						wall.Kill();
						bullet.Kill();
						break;
					}
				}
			}
		}
	}
}

bool Game::CheckCollision(Object& object1, Object& object2)
{
	if (object1.GetModel()->getGlobalBounds().intersects(object2.GetModel()->getGlobalBounds()))
	{
		if (object1.GetTeam() != object2.GetTeam())
		{
			return true;
		}
	}
	return false;
}

void Game::aiMove(const sf::Time &frameTime)
{
	for (int i = 0; i < enemies.size(); ++i)
	{
		if (enemies.at(i).IsAlive())
		{
			if (!enemyDescent)
			{
				enemies.at(i).Move(frameTime.asSeconds(), enemyDirection);
			}
			else
			{
				enemies.at(i).Descend();
				enemies.at(i).Move(frameTime.asSeconds(), enemyDirection);
			}
		}
	}
	enemyDescent = false;
}

void Game::playerFire()
{
	bullets.emplace_back();
	bullets.back().Initialize(player.GetPosX() + 9, player.GetPosY(), 1);
	player.SetShooting(true);
}

void Game::enemyFire()
{
	int enemyShoot;

	for (int i = 0; i < enemies.size(); ++i)
	{
		if (enemies.at(i).IsAlive())
		{
			enemyShoot = rand() % 10000;
			if (enemyShoot == 1)
			{
				bullets.emplace_back();
				bullets.back().Initialize(enemies.at(i).GetPosX(), enemies.at(i).GetPosY(), 2);
			}
		}
	}
}

bool Game::PlaceWall(int startPosX, int startPosY)
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			walls.emplace_back();
			walls.back().Initialize(startPosX + i * 15, startPosY + j * 15, 0);
		}
	}

	return true;
}

bool Game::CreatePlayer(int startPosX, int startPosY)
{
	player.Initialize(startPosX, startPosY, 1);
	return true;
}

bool Game::CreateEnemy(int startPosX, int startPosY)
{
	enemies.emplace_back();
	enemies.back().Initialize(startPosX, startPosY, 2);
	return true;
}

void Game::FinishGameCheck(sf::RenderWindow * window, const sf::Time &frameTime)
{
	if (!player.IsAlive())
	{
		finished = true;		
	}

	bool isAnyEnemyAlive = false;
	for (auto& enemy : enemies) //Check if any enemy is alive
	{
		if (enemy.IsAlive())
		{
			isAnyEnemyAlive = true;
		}
	}

	if (!isAnyEnemyAlive) // Victory if all enemies are dead
	{
		victory = true;
		finished = true;
	}
}
