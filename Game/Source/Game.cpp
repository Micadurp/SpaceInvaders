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

	for each(Enemy enemy in enemies)
	{
		enemy.Shutdown();
	}
	for each(Wall wall in walls)
	{
		wall.Shutdown();
	}
	for each(Bullet bullet in bullets)
	{
		bullet.Shutdown();
	}

	return true;
}

int Game::RenderGame(sf::RenderWindow * window, const sf::Time &frameTime)
{
	FinishGameCheck(window, frameTime);

	if (!finished)
	{
		//InputCheck(frameTime.asSeconds());

		for (int i = 0; i < bullets.size(); ++i)
		{
			if (bullets.at(i).IsAlive())
			{
				if (bullets.at(i).GetPosY() < -1)
				{
					bullets.at(i).Kill();
					continue;
				}

				if (BulletCollision(bullets.at(i), player))
				{
					player.Kill();
				}

				for (int j = 0; j < enemies.size(); ++j)
				{
					if (enemies.at(j).IsAlive())
					{
						if (BulletCollision(bullets.at(i), enemies.at(j)))
						{
							scoreHandler->ChangeScore(enemies.at(j).GetPoints());
							enemies.at(j).Kill();
							bullets.at(i).Kill();
							break;
						}
					}
				}

				for (int j = 0; j < walls.size(); ++j)
				{
					if (walls.at(j).IsAlive())
					{
						if (BulletCollision(bullets.at(i), walls.at(j)))
						{
							walls.at(j).Kill();
							bullets.at(i).Kill();
							break;
						}
					}
				}
			}
		}

		aiMove(frameTime);
		enemyFire();

		window->draw(*player.GetModel());
		for (int i = 0; i < bullets.size(); ++i)
		{
			if (bullets.at(i).IsAlive())
			{
				bullets.at(i).Move(100 * frameTime.asSeconds());
				window->draw(*bullets.at(i).GetModel());
			}
		}
		for (int i = 0; i < enemies.size(); ++i)
		{
			if (enemies.at(i).IsAlive())
			{
				if ((enemies.at(i).GetPosX() < 0 || enemies.at(i).GetPosX() > 800) && !enemyDescent)
				{
					enemyDirection = !enemyDirection;
					enemyDescent = true;

					if (enemies.at(i).GetPosX() < 0)
					{
						boundaryCompensation = -enemies.at(i).GetPosX();
					}
					else
					{
						boundaryCompensation = 800 - enemies.at(i).GetPosX();
					}
				}
				window->draw(*enemies.at(i).GetModel());
			}
		}

		for (int i = 0; i < walls.size(); ++i)
		{
			if (walls.at(i).IsAlive())
			{
				window->draw(*walls.at(i).GetModel());
			}
		}

		window->draw(scoreHandler->GetTotalScore());
		window->draw(scoreHandler->GetHighScore());
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

void Game::InputCheck(const float &frameTime)
{
	if (sf::Event::KeyPressed)
	{
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

bool Game::BulletCollision(Bullet& bullet, Object& object)
{
	if (bullet.GetModel()->getGlobalBounds().intersects(object.GetModel()->getGlobalBounds()))
	{
		if (bullet.GetTeam() != object.GetTeam())
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
		enemyShoot = rand() % 10000;
		if (enemyShoot == 1)
		{
			bullets.emplace_back();
			bullets.back().Initialize(enemies.at(i).GetPosX(), enemies.at(i).GetPosY(), 2);
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

	if (enemies.size() <= 0)
	{
		victory = true;
		finished = true;
	}
}
