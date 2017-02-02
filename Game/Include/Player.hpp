#ifndef PLAYER_H
#define PLAYER_H

#include"Object.hpp"

class Player : public Object
{
private:
	bool shooting;

public:
	Player();
	virtual ~Player();

	bool Initialize(float positionX, float positionY, int team) override;
	float Move(float move);
	bool IsShooting();
	void setShooting(bool shooting);

	sf::CircleShape * GetModel() override;
};

#endif