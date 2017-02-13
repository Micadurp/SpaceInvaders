#ifndef PLAYER_H
#define PLAYER_H

#include "Object.hpp"

class Player : public Object
{
private:
	bool shooting;
	float movespeed;

public:
	Player();
	virtual ~Player();

	bool Initialize(float positionX, float positionY, int team) override;
	// Move player in a direction at movementspeed. Deltatime should be in seconds. false = left , true = right
	float Move(const float &pDT, const bool &direction);
	bool IsShooting();
	void SetShooting(bool shooting);

	sf::CircleShape * GetModel() override;
};

#endif