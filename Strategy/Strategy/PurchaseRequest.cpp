#include "PurchaseRequest.h"

PurchaseRequest::PurchaseRequest(sf::Uint32 requestID, sf::Uint8 shopID, Player* player, Point* point) :
	player(player), point(point)
{
	PacketProperties properties(requestID, PacketType::REQUEST, SubType::REQUEST_SHOP_PURCHASE);

	this->sendProperties = properties;

	this->sendPacket << properties << shopID;
}

PurchaseRequest::~PurchaseRequest()
{
	printf("shop purchase request terminated: ");

	//*(this->communicatorStatus) = CommunicatorStatus::FAILED;

	Request::~Request();
}

void PurchaseRequest::update()
{
	Request::update();
	if (this->status == RequestStatus::RESPONDED)
	{
		sf::Uint8 shopID;
		sf::Uint8 previousOwnerID;
		sf::Uint32 cost;
		sf::Int32 cashRemain;
		sf::Int32 cap;

		switch (receiveProperties.requestValidity)
		{
		case RequestValidity::VALID:
			this->receivePacket >> shopID >> previousOwnerID >> cost >> cashRemain >> cap;
			player->purchase(point, cashRemain, cap);
			point->requestInfo = true;
			break;
		case RequestValidity::NOT_ON_SITE:
			this->receivePacket >> shopID;
			printf("Not on site: %d\n", shopID);
			break;
		case RequestValidity::INSUFFICIENT_CASH:
			printf("Not enough money\n");
			break;
		case RequestValidity::FREQUENT_PURCHASE:
			printf("Frequent purchase\n");
			break;
		default:
			break;
		}

		point->updatePopUpInfo = true;
		player->disablePurchase = false;
	}

	else if (this->status == RequestStatus::TIMEOUT)
	{
		printf("Purchase timeout\n");
		point->updatePopUpInfo = true;
		player->disablePurchase = false;
	}
}
