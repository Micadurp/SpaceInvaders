#include "Game.hpp"

Game::Game()
{
	player = nullptr;
}

Game::~Game()
{
	Destroy();
}

bool Game::Initialize(Score * score)
{
	scoreHandler = score;
	// TODO Give ability to choose different setups
	return defaultSetup();
}

bool Game::Destroy()
{
	if (player)
	{
		player->Shutdown();
		delete player;
		player = 0;
	}

	while (enemies.size()>0)
	{
		enemies.back()->Shutdown();
		delete enemies.back();
		enemies.pop_back();
	}

	while (walls.size()>0)
	{
		walls.back()->Shutdown();
		delete walls.back();
		walls.pop_back();
	}

	while (bullets.size()>0)
	{
		bullets.back()->Shutdown();
		delete bullets.back();
		bullets.pop_back();
	}

	return true;
}

bool Game::defaultSetup()
{
	player = new Player();
	player->Initialize(400, 570, 1);
	for (int i = 0; i < 9; ++i)
	{
		for (int j = 0; j < 8; ++j)
		{
			enemies.push_back(new Enemy());
			enemies.back()->Initialize(225 + i * 40, j * 40, 2);
		}
	}
	enemyDirection = true;

	PlaceWall(150, 500);
	PlaceWall(350, 500);
	PlaceWall(550, 500);

	finished = false;
	victory = false;

	return true;
}

int Game::RenderGame(sf::RenderWindow * window, const sf::Time &frameTime)
{
	FinishGameCheck(window, frameTime);

	if (!finished)
	{
		if (sf::Event::KeyPressed)
		{
			InputCheck(frameTime);
		}

		for (int i = 0; i < bullets.size(); ++i)
		{

			if (BulletCollision(bullets.at(i), player))
			{
				player->SetAlive(false);
			}

			for (int j = 0; j < enemies.size(); ++j)
			{
				if (BulletCollision(bullets.at(i), enemies.at(j)))
				{
					scoreHandler->ChangeScore(enemies.at(j)->GetPoints());
					enemies.at(j)->Shutdown();
					delete enemies.at(j);
					enemies.erase(enemies.begin() + j);
					bullets.at(i)->SetAlive(false);
					break;
				}
			}

			for (int j = 0; j < walls.size(); ++j)
			{
				if (BulletCollision(bullets.at(i), walls.at(j)))
				{
					walls.at(j)->Shutdown();
					delete walls.at(j);
					walls.erase(walls.begin() + j);
					bullets.at(i)->SetAlive(false);
					break;
				}
			}

			if (bullets.at(i)->GetPosY() < -1 || !bullets.at(i)->IsAlive())
			{
				bullets.at(i)->Shutdown();
				delete bullets.at(i);
				bullets.erase(bullets.begin() + i);
			}
		}

		aiMove(frameTime);
		enemyFire();

		window->draw(*player->GetModel());
		for (int i = 0; i < bullets.size(); ++i)
		{
			bullets.at(i)->Move(100 * frameTime.asSeconds());
			window->draw(*bullets.at(i)->GetModel());
		}
		for (int i = 0; i < enemies.size(); ++i)
		{
			if ((enemies.at(i)->GetPosX() < 0 || enemies.at(i)->GetPosX() > 800) && !enemyDescent)
			{
				enemyDirection = !enemyDirection;
				enemyDescent = true;

				if (enemies.at(i)->GetPosX() < 0)
				{
					boundaryCompensation = -enemies.at(i)->GetPosX();
				}
				else
				{
					boundaryCompensation = 800 - enemies.at(i)->GetPosX();
				}
			}
			window->draw(*enemies.at(i)->GetModel());
		}

		for (int i = 0; i < walls.size(); ++i)
		{
			window->draw(*walls.at(i)->GetModel());
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

void Game::InputCheck(const sf::Time &frameTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		player->Move(frameTime.asSeconds(), true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		player->Move(frameTime.asSeconds(), false);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !player->IsShooting())
	{
		bullets.push_back(new Bullet());
		bullets.back()->Initialize(player->GetPosX() + 9, player->GetPosY(), 1);
		player->SetShooting(true);
	}
	else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		player->SetShooting(false);
	}
}

bool Game::BulletCollision(Bullet * bullet, Object * object)
{
	if (bullet->GetModel()->getGlobalBounds().intersects(object->GetModel()->getGlobalBounds()))
	{
		if (bullet->GetTeam() != object->GetTeam())
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
		if (!enemyDescent)
		{
			if (enemyDirection)
			{
				enemies.at(i)->Move(100 * frameTime.asSeconds());
			}
			else
			{
				enemies.at(i)->Move(-100 * frameTime.asSeconds());
			}

		}
		else 
		{
			enemies.at(i)->Move(boundaryCompensation);
			enemies.at(i)->Descend();
		}
	}
	enemyDescent = false;
}

void Game::enemyFire()
{
	int enemyShoot;

	for (int i = 0; i < enemies.size(); ++i)
	{
		enemyShoot = rand() % 10000;
		if (enemyShoot == 1)
		{
			bullets.push_back(new Bullet());
			bullets.back()->Initialize(enemies.at(i)->GetPosX(), enemies.at(i)->GetPosY(), 2);
		}
	}
}	

bool Game::PlaceWall(int startPosX, int startPosY)
{
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			walls.push_back(new Wall());
			walls.back()->Initialize(startPosX + i * 20, startPosY + j * 20, 0);
		}
	}

	return true;
}

void Game::FinishGameCheck(sf::RenderWindow * window, const sf::Time &frameTime)
{
	if (!player->IsAlive())
	{
		finished = true;		
	}

	if (enemies.size() <= 0)
	{
		victory = true;
		finished = true;
	}
}
