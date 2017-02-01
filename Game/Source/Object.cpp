#include "Object.h"

Object::Object()
{

}

Object::~Object()
{
	delete model;
	model = NULL;
}

bool Object::Initialize(float pPositionX, float pPositionY, int pTeam)
{
	positionX = pPositionX;
	positionY = pPositionY;
	team = pTeam;
	alive = true;
	
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