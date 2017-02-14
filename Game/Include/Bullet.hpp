#ifndef BULLET_H
#define BULLET_H

#include"Object.hpp"

class Bullet : public Object
{
private:
	sf::CircleShape model;
	bool direction;

public:
	Bullet();
	virtual ~Bullet();
	bool Initialize(float positionX, float positionY, int team) override;
	bool Kill() override;

	float Move(float distance);

	sf::CircleShape * GetModel() override;
};

#endif
