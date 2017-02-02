#include "Object.hpp"

Object::Object()
{

}

Object::~Object()
{
	Shutdown();
}

bool Object::Shutdown()
{
	if (model)
	{
		delete model;
		model = 0;
	}
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