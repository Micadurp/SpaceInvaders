#include "Object.hpp"

Object::Object()
{
	positionX = 0;
	positionY = 0;
	team = 0;
	alive = false;
}

Object::~Object()
{
}

bool Object::Shutdown()
{
	return true;
}

bool Object::Initialize(float pPositionX, float pPositionY, int pTeam)
{
	positionX = pPositionX;
	positionY = pPositionY;
	team = pTeam;
	alive = true;
	
	return true;
}

bool Object::Kill()
{
	alive = false;
	return true;
}

float Object::GetPosX()
{
	return positionX;
}

float Object::GetPosY()
{
	return positionY;
}

int Object::GetTeam()
{
	return team;
}

bool Object::IsAlive()
{
	return alive;
}

void Object::SetAlive(bool pAlive)
{
	alive = pAlive;
}