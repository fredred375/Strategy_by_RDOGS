#include "Point.h"
#include "Player.h"

Point::Point() :
	body(20.f), name(name), price(price), owner(nullptr)
{
	body.setOrigin(body.getRadius(), body.getRadius());
	body.setFillColor(sf::Color::Red);
}

Point::Point(float x, float y, std::wstring name, int price) :
	body(20.f), name(name), price(price), owner(nullptr)
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

Player* Point::getOwner() const
{
	return owner;
}

void Point::purchased(Player* player)
{
	//send message to original owner

	//send message to original owner

	owner = player;
}


