#include "Point.h"

Point::Point() :
	body(1), isPopUp(false)
{
	body.setOrigin(body.getRadius(), body.getRadius());
	body.setFillColor(sf::Color::Red);
	popUpWindow.setString(name);
}

Point::Point(float x, float y) :
	body(20), isPopUp(false)
{
	body.setOrigin(body.getRadius(), body.getRadius());
	body.setPosition(x, y);
	body.setFillColor(sf::Color::Red);
	popUpWindow.setString(name);
}

Point::Point(float x, float y, std::wstring name, sf::Font* font) :
	body(20), isPopUp(false), name(name), popUpWindow(font)
{
	body.setOrigin(body.getRadius(), body.getRadius());
	body.setPosition(x, y);
	body.setFillColor(sf::Color::Red);
	popUpWindow.setString(name);
}

void Point::draw(sf::RenderWindow* window)
{
	window->draw(body);
	if (isPopUp)
	{
		popUpWindow.draw(window);
	}
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

void Point::popUp(sf::RenderWindow* window)
{
	isPopUp = true;
	popUpWindow.initDraw(window);
}

void Point::update(MouseData* mouseData, bool& popUpActivated)
{
	popUpWindow.checkMouseData(mouseData, popUpActivated);
	if (!popUpActivated)
	{
		isPopUp = false;
	}
}
