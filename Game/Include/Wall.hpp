#ifndef WALL_H
#define WALL_H

#include"Object.hpp"

class Wall : public Object
{
private:
	sf::RectangleShape model;
public:
	Wall();
	virtual ~Wall();

	bool Initialize(float positionX, float positionY, int team) override;
	bool Kill() override;

	sf::RectangleShape * GetModel() override;
};

#endif