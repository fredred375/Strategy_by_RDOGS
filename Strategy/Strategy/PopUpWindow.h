#pragma once
#include"MouseData.h"
class PopUpWindow
{
private:
	sf::RectangleShape windowBody;
	sf::RectangleShape closeBody;
	sf::Font font;
	sf::Text text;

	void checkCloseWindow(MouseData* mouseData, bool& popUpActivated);
public:
	PopUpWindow();
	PopUpWindow(sf::Font* font);
	void draw(sf::RenderWindow* window);
	void setPosition(sf::Vector2f pos);
	void setString(const std::wstring& s);
	void initDraw(sf::RenderWindow* window); //only called when this window is sure to be drawn
	void checkMouseData(MouseData* mouseData, bool& popUpActivated);
};

