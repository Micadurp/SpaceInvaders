#include "Player.hpp"


Player::Player() : shooting(false) , movespeed(200) , Object() {}

Player::~Player()
{
	Shutdown();
}

bool Player::Initialize(float pPositionX, float pPositionY, int team)
{
	Object::Initialize(pPositionX, pPositionY, team);
	shooting = false;
	model = new sf::CircleShape(10.f);
	model->setFillColor(sf::Color::Green);
	model->setPosition(pPositionX, pPositionY);

	LuaScript* playerScript = new LuaScript("Scripts/player.lua");
	movespeed = playerScript->GetVariable<float>("m_moveSpeed");
	delete playerScript;

	return true;
}

float Player::Move(const float &pDT, const bool &pDirection)
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

bool Player::IsShooting()
{
	return shooting;
}

void Player::SetShooting(bool pShooting)
{
	shooting = pShooting;
}

sf::CircleShape * Player::GetModel()
{
	return (sf::CircleShape*) model;
}
