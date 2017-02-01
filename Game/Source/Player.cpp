#include "Player.h"


Player::Player() : Object()
{

}

Player::~Player()
{

}

bool Player::Initialize(float pPositionX, float pPositionY, int team)
{
	Object::Initialize(pPositionX, pPositionY, team);
	shooting = false;
	model = new sf::CircleShape(10.f);
	model->setFillColor(sf::Color::Green);
	model->setPosition(pPositionX, pPositionY);

	return true;
}

float Player::Move(float move)
{
	positionX += move;
	model->move(move, 0);
	return positionX;
}

bool Player::IsShooting()
{
	return shooting;
}

void Player::setShooting(bool pShooting)
{
	shooting = pShooting;
}

sf::CircleShape * Player::GetModel()
{
	return (sf::CircleShape*) model;
}
