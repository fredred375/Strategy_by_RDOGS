#pragma once
#include "Communicator.h"
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
	Point* getPoint() const { return point; }
	void initDraw(sf::View view);
	void draw(sf::RenderWindow* window);
};

