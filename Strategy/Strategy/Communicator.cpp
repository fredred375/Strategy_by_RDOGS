#include "Communicator.h"

// Code for client communicator



Communicator::Communicator()
	: 
	currentRequestID(0), 
	serverAddress(sf::IpAddress("1.162.47.226")),
	socket(new sf::TcpSocket), 
	status(CommunicatorStatus::DISCONNECTED), 
	connectRequest(nullptr)
{
	this->socket->setBlocking(false);
}

Communicator::Communicator(std::string serverAddress)
	: 
	currentRequestID(0), 
	serverAddress(sf::IpAddress("10.1.1.21")),
	socket(new sf::TcpSocket), 
	status(CommunicatorStatus::DISCONNECTED), 
	connectRequest(nullptr)
{
	this->socket->setBlocking(false);
}

Communicator::~Communicator()
{
}

void Communicator::update()
{
	if (this->status == CommunicatorStatus::DISCONNECTED)
	{
		printf("initiating new connect request...\n");

		connectRequest = this->requestConnect(this->teamID);

		if (connectRequest)
		{
			this->requests.push_back(this->connectRequest);
		}

		this->status = CommunicatorStatus::REQUESTED;
	}

	else if (this->status == CommunicatorStatus::FAILED)
	{
		printf("initiating new connect request (previous failed...\n");
		
		connectRequest = this->requestConnect(this->teamID);

		this->requests.push_back(this->connectRequest);

		if (connectRequest)
		{
			this->requests.push_back(this->connectRequest);
		}

		this->status = CommunicatorStatus::REQUESTED;
	}

		//else // already requested
		//{
		//	RequestStatus requestStatus = this->connectRequest->getStatus();
		//	if (requestStatus ==  RequestStatus::RESPONDED)
		//	{
		//		sf::Packet responsePacket = this->connectRequest->getResponsePacket();

		//		PacketProperties responsePacketProperties;
		//		sf::Uint8 teamID;
		//		responsePacket >> responsePacketProperties;

		//		switch (responsePacketProperties.requestValidity)
		//		{
		//		case RequestValidity::VALID:

		//			responsePacket >> teamID;
		//			printf("connected! team ID is %d\n", teamID);

		//			this->status = CommunicatorStatus::CONNECTED;

		//			break;


		//		case RequestValidity::INVALID_TEAM_ID:

		//			printf("not connected: invalid team ID...\n");

		//			break;


		//		default:

		//			printf("i don't know what happend but you're fucked up...\n");

		//			break;
		//		}
		//	}
		//	else if (requestStatus == RequestStatus::TIMEOUT) //  request timeout
		//	{
		//		printf("connect request timeout, retrying...");

		//		delete this->connectRequest;
		//		this->connectRequest = nullptr;
		//	}
		//}
	

	else
	{
		sf::Packet tempReceivePacket;

		if (this->socket->receive(tempReceivePacket) == sf::Socket::Status::Done) // Receive
		{
			PacketProperties tempReceivePacketProperties;

			tempReceivePacket >> tempReceivePacketProperties;

			bool isResponse = false;

			for (size_t i = 0; i < this->requests.size(); i++)
			{
				if (tempReceivePacketProperties.ID == this->requests[i]->sendProperties.ID) // response for this request
				{
					isResponse = true;

					requests[i]->receivePacket = tempReceivePacket;
					requests[i]->receiveProperties = tempReceivePacketProperties;

					requests[i]->status = RequestStatus::RESPONDED;
				}
			}

			if (!isResponse) //  server send or broadcast
			{
				this->receives.push(tempReceivePacket);
			}

			
			if (!this->sends.empty()) // Pending sends
			{
				sf::Packet sendingPacket = this->sends.front();

				if (this->socket->send(sendingPacket)) // Send
				{
					this->sends.pop();
				}

				else // Send failed
				{
					this->status = CommunicatorStatus::DISCONNECTED;
				}
			}
		}

		else // Receive failed
		{
			this->status = CommunicatorStatus::DISCONNECTED;
		}
	}

	// Update Requests
	for (size_t i = 0; i < requests.size(); i++)
	{
		Request* tempRequest = this->requests[i];

		//if (*tempRequest == ConnectRequest()) // deleted elsewhere
		//{
		//	this->requests.erase(this->requests.begin() + i);
		//}

		
		{
			if (tempRequest->status == RequestStatus::PENDING)
			{
				this->sends.push(tempRequest->sendPacket);
			}

			tempRequest->update();

			if (tempRequest->status == RequestStatus::RESPONDED || tempRequest->status == RequestStatus::TIMEOUT) // Done
			{
				delete tempRequest;
				this->requests.erase(this->requests.begin() + i);
			}
		}
	}

}

ConnectRequest* Communicator::requestConnect(sf::Uint8 teamID)
{
	printf("connecting to ");
	std::cout << this->serverAddress.toString() << "\n";

	if (this->socket->connect(serverAddress, 2000) != sf::Socket::Done)
	{
		printf("socket error connecting to server...\n");
		return nullptr;
	}

	printf("socket is connected to server! sending login request...\n");

	// "hello" message / login
	ConnectRequest* request = new ConnectRequest(this->getCurrentRequestID(), this->teamID, &(this->status));

	request->sendPacket << teamID;

	this->requests.emplace_back(request);

	return request;
}