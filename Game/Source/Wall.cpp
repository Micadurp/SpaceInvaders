#include "Wall.hpp"

Wall::Wall() : Object()
{

}

Wall::~Wall()
{
	Shutdown();
}

bool Wall::Initialize(float pPositionX, float pPositionY, int team)
{
	Object::Initialize(pPositionX, pPositionY, team);	
	model = sf::RectangleShape(sf::Vector2f(15.f, 15.f));
	model.setFillColor(sf::Color::Blue);
	model.setPosition(pPositionX, pPositionY);

	return true;
}

bool Wall::Kill()
{
	Object::Kill();
	return true;
}

sf::RectangleShape * Wall::GetModel()
{
	return &model;
}
