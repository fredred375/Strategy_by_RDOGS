#include "Player.h"
#include "Point.h"

Player::Player() :
	playerBody(20.f), playerId(-1), movementSpeed(300.f), cash(10000), arrived(true), dest(nullptr), updatePosUI(false), updateCashUI(false)
{
	playerBody.setOrigin(playerBody.getRadius(), playerBody.getRadius());
	playerBody.setFillColor(sf::Color::Black);
}

Player::Player(int playerId) :
	playerBody(20.f), playerId(playerId), movementSpeed(300.f), cash(10000), arrived(true), dest(nullptr), updatePosUI(false), updateCashUI(false)
{
	playerBody.setOrigin(playerBody.getRadius(), playerBody.getRadius());
	playerBody.setPosition(1793.26f, 1799.24f);
	playerBody.setFillColor(sf::Color::Black);
}

void Player::moveToPoint(Point* dest)
{
	if (dest == this->dest)
	{
		return;
	}
	this->dest = dest;
	this->arrived = false;
	sf::Vector2f distance = dest->getPosition() - playerBody.getPosition();
	unitVec = distance / sqrt(pow(distance.x, 2) + pow(distance.y, 2));
	updatePosUI = true;
}

void Player::update(const float& dt)
{
	if (!arrived)
	{
		sf::Vector2f nextStep = unitVec * movementSpeed * dt;
		if (abs(nextStep.x) >= abs(dest->getPosition().x - playerBody.getPosition().x))//this means that we will move over the dest
		{
			playerBody.setPosition(dest->getPosition());
			arrived = true;
			updatePosUI = true;
		}
		else
		{
			playerBody.setPosition(playerBody.getPosition() + nextStep);
		}
	}
}

void Player::purchase(Point* point)
{
	if (cash >= point->getPrice())
	{
		properties.push_back(point);
		cash -= point->getPrice();
		point->purchased(this);
		updateCashUI = true;
	}
}
