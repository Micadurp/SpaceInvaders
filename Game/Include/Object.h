#ifndef OBJECT_H
#define OBJECT_H

#include <SFML\Graphics.hpp>

class Object
{
protected:
	float positionX;
	float positionY;
	int team;
	bool alive;
	sf::Shape * model;

public:
	Object();
	virtual ~Object();

	virtual bool Initialize(float positionX, float positionY, int team) = 0;
	virtual bool Shutdown();

	float GetPosX();
	float GetPosY();
	int GetTeam();
	bool IsAlive();
	void SetAlive(bool alive);
	virtual sf::Shape * GetModel() = 0;
};


#endif 
