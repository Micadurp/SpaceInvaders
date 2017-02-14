#include "Enemy.hpp"


Enemy::Enemy() : pointWorth(100), movespeed(100), Object()
{
}

Enemy::~Enemy()
{
}

bool Enemy::Initialize(float pPositionX, float pPositionY, int team)
{
	Object::Initialize(pPositionX, pPositionY, team);
	model = sf::CircleShape(10.f);
	model.setFillColor(sf::Color::White);
	model.setPosition(pPositionX, pPositionY);
	
	return true;
}

bool Enemy::Kill()
{
	Object::Kill();
	return true;
}

float Enemy::Move(const float &pDT, const bool &pDirection)
{
	if (pDirection)
	{
		positionX += movespeed * pDT;
		model.move(movespeed * pDT, 0);
	}
	else
	{
		positionX -= movespeed * pDT;
		model.move(-movespeed * pDT, 0);
	}
	return positionX;
}

void Enemy::Descend()
{
	positionY += 10;
	model.move(0, 10);
}

sf::CircleShape * Enemy::GetModel()
{
	return &model;
}

long Enemy::GetPoints()
{
	return pointWorth;
}
