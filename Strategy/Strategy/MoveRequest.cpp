#include "MoveRequest.h"

MoveRequest::MoveRequest(sf::Uint32 requestID, sf::Uint8 shopID, Player* player, Point* point) :
	player(player), point(point)
{
	PacketProperties properties(requestID, PacketType::REQUEST, SubType::REQUEST_MOVE);

	this->sendProperties = properties;

	this->sendPacket << properties << shopID;
}

MoveRequest::~MoveRequest()
{
	printf("move request terminated: ");

	//*(this->communicatorStatus) = CommunicatorStatus::FAILED;

	Request::~Request();
}

void MoveRequest::update()
{
	Request::update();
	if (this->status == RequestStatus::RESPONDED)
	{
		sf::Uint8 shopID;
		sf::Uint16 time;

		switch (receiveProperties.requestValidity)
		{
		case RequestValidity::VALID:
			this->receivePacket >> shopID >> time;
			player->moveToPoint(point, time);
			break;
		default:
			break;
		}
		player->disableMove = false;
	}

	else if (this->status == RequestStatus::TIMEOUT)
	{
		printf("Move timeout\n");
		player->disableMove = false;
	}
}
