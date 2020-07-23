#pragma once
#include "PopUpWindow.h"
class Point
{
private:
	sf::CircleShape body;
	PopUpWindow popUpWindow;
	std::wstring name;

	bool isPopUp;
public:
	Point();
	Point(float x, float y);
	Point(float x, float y, std::wstring name, sf::Font* font);
	void draw(sf::RenderWindow* window);
	bool clicked(float mouseX, float mouseY);
	void popUp(sf::RenderWindow* window);
	void update(MouseData* mouseData, bool& popUpActivated);
};

