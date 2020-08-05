#pragma once
#include "MouseData.h"
#include "Player.h"
class Player;
class Point
{
private:
	sf::CircleShape body;
	std::wstring name;
	int price;
	Player* owner;

public:
	Point();
	Point(float x, float y, std::wstring name, int price);
	std::wstring getName() const { return name; }
	void draw(sf::RenderWindow* window);
	bool clicked(float mouseX, float mouseY);
	Player* getOwner() const;
	int getPrice() const { return price; }
	sf::Vector2f getPosition() const { return body.getPosition(); }
	void purchased(Player* player);
};

