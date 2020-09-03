#pragma once
<<<<<<< HEAD
#include "Point.h"
=======
#include "MouseData.h"
>>>>>>> socket
class Point;
class Player
{
private:
	int playerId;
	int cash;
<<<<<<< HEAD
	std::vector<Point*> properties;
=======
	int cap;
	std::vector<Point*> properties;
	sf::Texture* texture;
>>>>>>> socket
	sf::CircleShape playerBody;
	const float movementSpeed;

	Point* dest;
	sf::Vector2f unitVec;
	bool arrived;
<<<<<<< HEAD
=======
	std::vector<Point>* pointList;
>>>>>>> socket

public:
	bool updatePosUI;
	bool updateCashUI;
<<<<<<< HEAD
	Player();
	Player(int playerId);
	sf::Vector2f getPosition() const { return playerBody.getPosition(); }
	int getCash() const { return cash; }
	int getID() const { return playerId; }
	bool getArrived() const { return arrived; }
	Point* getPoint() { return dest; }
	std::vector<Point*> getProperties() const { return properties; }
	void draw(sf::RenderWindow* window) { window->draw(playerBody); }
	void moveToPoint(Point* dest);
	void update(const float& dt);
	void purchase(Point* point);
=======
	bool updateCapUI;
	bool updateTeamUI;
	bool updateInfoBox;
	bool disableMove;
	bool disablePurchase;
	Player(int playerId, sf::Texture* texture);
	sf::Vector2f getPosition() const { return playerBody.getPosition(); }
	int getCash() const { return cash; }
	void setCash(int cash)
	{
		this->cash = cash;
		updateCashUI = true;
	}
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
>>>>>>> socket
};

