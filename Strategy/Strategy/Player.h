#pragma once
#include "Point.h"
class Point;
class Player
{
private:
	int playerId;
	int cash;
	std::vector<Point*> properties;
	sf::CircleShape playerBody;
	const float movementSpeed;

	Point* dest;
	sf::Vector2f unitVec;
	bool arrived;

public:
	bool updatePosUI;
	bool updateCashUI;
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
};

