#pragma once
#include"MouseData.h"
class Point
{
private:
	sf::CircleShape body;
	std::wstring name;

public:
	Point();
	Point(float x, float y);
	Point(float x, float y, std::wstring name);
	std::wstring getName() const { return name; }
	void draw(sf::RenderWindow* window);
	bool clicked(float mouseX, float mouseY);
};

