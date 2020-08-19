#include "ConnectRequest.h"

ConnectRequest::ConnectRequest()
	: Request(), communicatorStatus(nullptr)
{
}

ConnectRequest::ConnectRequest(sf::Uint32 requestID, sf::Uint8 teamID, CommunicatorStatus* status)
	: Request(), communicatorStatus(status)
{
	PacketProperties properties(requestID, PacketType::REQUEST, SubType::REQUEST_CONNECT);

	this->sendPacket << properties << teamID;
}

ConnectRequest::~ConnectRequest()
{
	printf("connect request terminated: ");
	Request::~Request();
}

void ConnectRequest::update()
{
	if (this->status == RequestStatus::RESPONDED)
	{
		this->receivePacket >> this->receiveProperties;

		switch (receiveProperties.requestValidity)
		{
		case RequestValidity::VALID:

			printf("connected to server successfully!\n");
			*(this->communicatorStatus) = CommunicatorStatus::CONNECTED;

		case RequestValidity::INVALID_TEAM_ID:

			printf("invlid team id...\n");
			*(this->communicatorStatus) = CommunicatorStatus::FAILED;

		default:
			break;
		}
	}

	else if (this->status == RequestStatus::TIMEOUT)
	{
		*(this->communicatorStatus) = CommunicatorStatus::FAILED;
	}
}
