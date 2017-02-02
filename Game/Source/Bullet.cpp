#include "Bullet.hpp"

Bullet::Bullet() : Object()
{

}

Bullet::~Bullet()
{
	Shutdown();
}

bool Bullet::Initialize(float pPositionX, float pPositionY, int team)
{
	Object::Initialize(pPositionX, pPositionY, team);

	model = new sf::CircleShape(2.f);

	if (team == 2)
	{
		model->setFillColor(sf::Color::Red);
		direction = false;
	}
	else 
	{
		model->setFillColor(sf::Color::Magenta);
		direction = true;
	}

	model->setPosition(pPositionX, pPositionY);

	return true;
}



float Bullet::Move(float distance)
{
	if (direction == true)
	{
		positionY -= distance;
		model->move(0, -distance);
	}
	else
	{
		positionY += distance;
		model->move(0, distance);
	}
	return positionY;
}

sf::CircleShape * Bullet::GetModel()
{
	return (sf::CircleShape*) model;
}
