#include "Player.h"
#include "Point.h"


Player::Player(int playerId, sf::Texture* texture) :
	playerBody(25.f), playerId(playerId), movementSpeed(300.f), cash(2500000), cap(0),
	arrived(true), dest(nullptr), updatePosUI(false), updateCashUI(false),
	updateInfoBox(false), disableMove(false), disablePurchase(false), texture(texture)
{
	playerBody.setOrigin(playerBody.getRadius(), playerBody.getRadius());
	playerBody.setPosition(1793.26f, 1799.24f);
	//playerBody.setFillColor(sf::Color::Black);
	playerBody.setTexture(this->texture);
}

void Player::setCash(int cash)
{
	this->cash = cash;
	updateCashUI = true;
}


void Player::setPosition(Point* point)
{
	this->dest = point;
	arrived = true;
	if (point->getOwnerID() == this->getID())
	{
		point->setNonPurchasable();
	}
	playerBody.setPosition(point->getPosition());
	updatePosUI;
}

bool Player::removeProperty(int shopID)
{
	updateInfoBox = true;
	updateCapUI = true;
	for (int i = 0; i < properties.size(); i++)
	{
		if (properties.at(i)->getID() == shopID)
		{
			properties.erase(properties.begin() + i);
			return true;
		}
	}
	return false;
}

bool Player::addProperty(Point* point)
{
	properties.push_back(point);
	return true;
}

void Player::moveToPoint(Point* dest, sf::Uint16 time)
{
	if (time == 0)
	{
		return;
	}
	this->dest = dest;
	this->arrived = false;
	sf::Vector2f distance = dest->getPosition() - playerBody.getPosition();
	unitVec = distance / (float)time;
	updatePosUI = true;
}

void Player::update(const float& dt)
{
	if (!arrived)
	{
		sf::Vector2f nextStep = unitVec * dt;
		if (abs(nextStep.x) >= abs(dest->getPosition().x - playerBody.getPosition().x))//this means that we will move over the dest
		{
			playerBody.setPosition(dest->getPosition());
			arrived = true;
			if (this->dest->getOwnerID() == this->getID()) //  revisit
			{
				this->dest->setNonPurchasable();
			}
			updatePosUI = true;
		}
		else
		{
			playerBody.setPosition(playerBody.getPosition() + nextStep);
		}
	}
}

void Player::purchase(Point* point, int remain, int cap)
{
	properties.push_back(point);
	cash = remain;
	this->cap = cap;
	point->purchased(this);
	updateCashUI = true;
	updateCapUI = true;
	updateInfoBox = true;
}

void Player::setColor(sf::Color color)
{
	playerBody.setFillColor(color);
}

void Player::setProperties(std::vector<sf::Uint8> properties)
{
	if (pointList)
	{
		this->properties.clear();
		for (const auto& shopID : properties)
		{
			this->properties.push_back(&pointList->at(shopID - 1));
		}
	}
}

void Player::setDest(sf::Uint8 destID)
{
	if (pointList)
	{
		if (destID > 0 && destID < pointList->size())
		{
			dest = &pointList->at(destID - 1);
		}
	}
}

bool Player::clicked(float mouseX, float mouseY)
{
	if (std::abs(mouseX - playerBody.getPosition().x) > playerBody.getRadius() || std::abs(mouseY - playerBody.getPosition().y) > playerBody.getRadius())
	{
		return false;
	}
	else
	{
		float distance = sqrt(pow(mouseX - playerBody.getPosition().x, 2) + pow(mouseY - playerBody.getPosition().y, 2));
		return (distance < playerBody.getRadius() ? true : false);
	}
}