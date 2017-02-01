#ifndef ENEMY_H
#define ENEMY_H

#include"Object.h"

class Enemy : public Object
{
private:
	long pointWorth;

public:
	Enemy();
	virtual ~Enemy();

	bool Initialize(float positionX, float positionY, int team) override;
	float Move(float move);
	void Descend();

	long GetPoints();

	sf::CircleShape * GetModel() override;
};

#endif