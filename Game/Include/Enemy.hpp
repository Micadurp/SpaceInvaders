#ifndef ENEMY_H
#define ENEMY_H

#include"Object.hpp"

class Enemy : public Object
{
private:
	sf::CircleShape model;
	long pointWorth;
	float movespeed;

public:
	Enemy();
	virtual ~Enemy();

	bool Initialize(float positionX, float positionY, int team) override;
	bool Kill() override;
	float Move(const float &pDT, const bool &pDirection);
	void Descend();

	long GetPoints();

	sf::CircleShape * GetModel() override;
};

#endif