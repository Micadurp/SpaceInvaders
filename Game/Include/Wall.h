#ifndef WALL_H
#define WALL_H

#include"Object.h"

class Wall : public Object
{
private:

public:
	Wall();
	virtual ~Wall();

	bool Initialize(float positionX, float positionY, int team) override;

	sf::RectangleShape * GetModel() override;
};

#endif