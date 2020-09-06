#pragma once
#include "MouseData.h"
class Point;
class Player
{
private:
	int playerId;
	int cash;
	int cap;
	std::vector<Point*> properties;
	sf::Texture* texture;
	sf::CircleShape playerBody;
	const float movementSpeed;

	Point* dest;
	sf::Vector2f unitVec;
	bool arrived;
	std::vector<Point>* pointList;

public:
	bool updatePosUI;
	bool updateCashUI;
	bool updateCapUI;
	bool updateTeamUI;
	bool updateInfoBox;
	bool disableMove;
	bool disablePurchase;
	Player(int playerId, sf::Texture* texture);
	sf::Vector2f getPosition() const { return playerBody.getPosition(); }
	int getCash() const { return cash; }
	void setCash(int cash);
	int getCap() { return this->cap; }
	void setCap(int cap) { this->cap = cap; updateCapUI = true; }
	void setPointList(std::vector<Point>* pointList) { this->pointList = pointList; }
	void setProperties(std::vector<sf::Uint8> properties);
	int getID() const { return playerId; }
	bool getArrived() const { return arrived; }
	Point* getPoint() { return dest; }
	void setPosition(Point* point);
	std::vector<Point*> getProperties() const { return properties; }
	bool removeProperty(int shopID);
	bool addProperty(Point* point);
	void draw(sf::RenderWindow* window) { window->draw(playerBody); }
	void moveToPoint(Point* dest, sf::Uint16 time);
	void update(const float& dt);
	void purchase(Point* point, int remain, int cap);
	void setColor(sf::Color color);
	void setDest(sf::Uint8 destID);
	bool clicked(float mouseX, float mouseY);
};

