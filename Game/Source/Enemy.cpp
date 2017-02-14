#include "Enemy.hpp"


Enemy::Enemy() : pointWorth(100), movespeed(100), Object()
{

}

Enemy::~Enemy()
{
	Shutdown();
}

bool Enemy::Initialize(float pPositionX, float pPositionY, int team)
{
	Object::Initialize(pPositionX, pPositionY, team);
	model = new sf::CircleShape(10.f);
	model->setFillColor(sf::Color::White);
	model->setPosition(pPositionX, pPositionY);

	/*LuaScript enemyScript = LuaScript();
	enemyScript.LoadData("Scripts/enemyStats.lua");
	pointWorth = enemyScript.GetVariable<float>("m_pointWorth");
	movespeed = enemyScript.GetVariable<float>("m_moveSpeed");*/

	return true;
}

float Enemy::Move(const float &pDT, const bool &pDirection)
{
	if (pDirection)
	{
		positionX += movespeed * pDT;
		model->move(movespeed * pDT, 0);
	}
	else
	{
		positionX -= movespeed * pDT;
		model->move(-movespeed * pDT, 0);
	}
	return positionX;
}

void Enemy::Descend()
{
	positionY += 10;
	model->move(0, 10);
}

sf::CircleShape * Enemy::GetModel()
{
	return (sf::CircleShape*) model;
}

long Enemy::GetPoints()
{
	return pointWorth;
}
