#pragma once
#include "Point.h"
#include "centerText.h"
class PopUpWindow
{
private:
	sf::RectangleShape windowBody;
	sf::RectangleShape closeBody;
	sf::RectangleShape purchaseBody;
	sf::Font* font;
	sf::Text nameText;
	sf::Text priceText;
	sf::Text ownerText;
	sf::Text purchaseText;
	Point* point;
	Player* player;
	bool canPurchase;
	void checkCloseWindow(MouseData* mouseData);
	void checkPurchase(MouseData* mouseData);
public:
	bool activated;
	PopUpWindow(Player* player, sf::Font* font);
	void draw(sf::RenderWindow* window);
	void setString(const std::wstring& s);
	void setPoint(Point* point);
	void initDraw(const sf::View& view); //only called when this window is sure to be drawn
	void checkMouseData(MouseData* mouseData);
	void update(MouseData* mouseData);
};

