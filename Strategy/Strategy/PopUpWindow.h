#pragma once
#include "Point.h"
class PopUpWindow
{
private:
	sf::RectangleShape windowBody;
	sf::RectangleShape closeBody;
	sf::Font font;
	sf::Text text;


	void setPosition(sf::Vector2f pos);
	void checkCloseWindow(MouseData* mouseData);
public:
	bool activated;
	PopUpWindow();
	PopUpWindow(sf::Font* font);
	void draw(sf::RenderWindow* window);
	void setString(const std::wstring& s);
	void setPoint(const Point& point);
	void initDraw(sf::RenderWindow* window); //only called when this window is sure to be drawn
	void checkMouseData(MouseData* mouseData);
	void update(MouseData* mouseData);
};

