#pragma once
<<<<<<< HEAD
#include "Point.h"
=======
#include "Communicator.h"
>>>>>>> socket
class PointHoverUI
{
private:
	sf::RectangleShape body;
	sf::Text text;
	Point* point;
public:
	bool activated;
	PointHoverUI(sf::Font* font);
	void setPoint(Point* point);
	void initDraw(sf::View view);
	void draw(sf::RenderWindow* window);
};

