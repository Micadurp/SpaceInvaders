#include "Enemy.hpp"


Enemy::Enemy() : Object()
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
	pointWorth = 100;

	return true;
}

float Enemy::Move(float move)
{
	positionX += move;
	model->move(move, 0);
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
