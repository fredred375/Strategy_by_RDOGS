#include "ShopInformationRequest.h"

ShopInformationRequest::ShopInformationRequest(sf::Uint32 requestID, sf::Uint8 shopID, Point* point)
	: Request(), point(point)
{
	PacketProperties properties(requestID, PacketType::REQUEST, SubType::REQUEST_SHOP_INFORMATION);

	this->sendProperties = properties;

	this->sendPacket << properties << shopID;
}

ShopInformationRequest::~ShopInformationRequest()
{
	printf("shop info request terminated: ");

	//*(this->communicatorStatus) = CommunicatorStatus::FAILED;

	Request::~Request();
}

void ShopInformationRequest::update()
{
	Request::update();
	if (this->status == RequestStatus::RESPONDED)
	{
		sf::Uint8 shopID;
		sf::Uint8 ownerID;
		sf::Uint32 capital;
		sf::Uint32 price;
		sf::Uint32 prevRevenue;
		sf::Uint16 transactionTimes;

		switch (receiveProperties.requestValidity)
		{
		case RequestValidity::VALID:
			this->receivePacket >> shopID  >> ownerID >> capital >> price >> prevRevenue >> transactionTimes;
			//point->setOwnerID(ownerID);
			point->setCapital(capital);
			point->setPrice(price);
			point->setPrevRevenue(prevRevenue);
			point->setTransactionTimes(transactionTimes);
			break;
		case RequestValidity::INVALID_SHOP_ID:
			printf("Please fix, invalid shop id\n");
			point->setOwnerID(-1);
			point->setCapital(-1);
			point->setPrice(-1);
			point->setPrevRevenue(-1);
			point->setTransactionTimes(-1);
			break;
		default:
			break;
		}

		point->updatePopUpInfo = true;

	}

	else if (this->status == RequestStatus::TIMEOUT)
	{
		point->setOwnerID(-2);
		point->setCapital(-2);
		point->setPrice(-2);
		point->setPrevRevenue(-2);
		point->setTransactionTimes(-2);
		point->updatePopUpInfo = true;
	}
}
