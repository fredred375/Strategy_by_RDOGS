#include "Point.h"

Point::Point() :
	body(1)
{
	body.setOrigin(body.getRadius(), body.getRadius());
	body.setFillColor(sf::Color::Red);
}

Point::Point(float x, float y) :
	body(20)
{
	body.setOrigin(body.getRadius(), body.getRadius());
	body.setPosition(x, y);
	body.setFillColor(sf::Color::Red);
}

Point::Point(float x, float y, std::wstring name) :
	body(20), name(name)
{
	body.setOrigin(body.getRadius(), body.getRadius());
	body.setPosition(x, y);
	body.setFillColor(sf::Color::Red);
}

void Point::draw(sf::RenderWindow* window)
{
	window->draw(body);
}

bool Point::clicked(float mouseX, float mouseY)
{
	if (mouseX - body.getPosition().x > body.getRadius() || mouseY - body.getPosition().y > body.getRadius())
	{
		return false;
	}
	else
	{
		float distance = sqrt(pow(mouseX - body.getPosition().x, 2) + pow(mouseY - body.getPosition().y, 2));
		return (distance < body.getRadius() ? true : false);
	}
	return false;
}


