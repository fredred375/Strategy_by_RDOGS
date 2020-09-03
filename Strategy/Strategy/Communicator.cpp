#include "Communicator.h"
#include "Player.h"
#pragma warning(disable : 26812)

// Code for client communicator

Communicator::Communicator()
	: 
	currentRequestID(0), 
	serverAddress(sf::IpAddress("10.1.1.12")),
	socket(new sf::TcpSocket), 
	status(CommunicatorStatus::DISCONNECTED), 
	connectRequest(nullptr)
{
	this->socket->setBlocking(false);
}

Communicator::Communicator(std::string serverAddress, sf::Uint8 teamID)
	: 
	currentRequestID(0), 
	serverAddress(sf::IpAddress(serverAddress)),
	socket(new sf::TcpSocket), 
	status(CommunicatorStatus::DISCONNECTED), 
	connectRequest(nullptr),
	teamID(teamID)
{
	this->socket->setBlocking(false);
}

Communicator::~Communicator()
{
	this->socket->disconnect();
}

void Communicator::update()
{
	//printf("updated\n");

	if (failCount > 30)
	{
		exit(3);
	}

	if (this->status == CommunicatorStatus::DISCONNECTED)
	{
		printf("initiating new connect request...\n");

		connectRequest = this->requestConnect(this->teamID);

		/*if (connectRequest != nullptr)
		{
		this->requests.push_back(this->connectRequest);
		}*/

		this->status = CommunicatorStatus::REQUESTED;

		this->failCount++;
	}

	else if (this->status == CommunicatorStatus::FAILED)
	{
		printf("initiating new connect request (previous failed...\n");

		connectRequest = this->requestConnect(this->teamID);

		/*if (connectRequest != nullptr)
		{
		this->requests.push_back(this->connectRequest);
		}*/

		this->status = CommunicatorStatus::REQUESTED;

		this->failCount++;
	}



	else
	{
		sf::Packet tempReceivePacket;

		sf::Socket::Status receiveStatus;

		int loop = 0;

		do
		{
			receiveStatus = this->socket->receive(tempReceivePacket);
			loop++;
		} while (receiveStatus == sf::Socket::Partial && loop < 100);

		switch (receiveStatus)
		{
		case sf::Socket::Done:
		{
			printf("received packet from server\n");

			PacketProperties tempReceivePacketProperties;

			tempReceivePacket >> tempReceivePacketProperties;


			if (tempReceivePacketProperties.packetType == PacketType::RESPONSE)
			{
				for (size_t i = 0; i < this->requests.size(); i++)
				{
					if (tempReceivePacketProperties.ID == this->requests[i]->sendProperties.ID) // response for this request
					{
						requests[i]->receivePacket = tempReceivePacket;
						requests[i]->receiveProperties = tempReceivePacketProperties;

						requests[i]->status = RequestStatus::RESPONDED;

						break;
					}
				}

				// no break implies request timeout or other error
			}


			else // server send or broadcast
			{
				tempReceivePacket << tempReceivePacketProperties;
				this->receives.push(std::make_pair(tempReceivePacket, tempReceivePacketProperties));
			}
		}

		break;


		case sf::Socket::NotReady:

			//printf("no receives\n");

			break;

		case sf::Socket::Disconnected:
			break;
		case sf::Socket::Error:
			break;
		default:
			break;
		}


		if (!this->sends.empty()) // Pending sends
		{
			sf::Packet sendingPacket = this->sends.front();

			sf::Socket::Status sendStatus;
			loop = 0;

			do
			{
				sendStatus = this->socket->send(sendingPacket);
				loop++;
			} while (sendStatus == sf::Socket::Partial && loop < 100);

			if (sendStatus == sf::Socket::Status::Done) // Send
			{
				printf("packet sent successfully!\n");
				this->sends.pop();
			}

			else // Send failed
			{
				printf("error sending packet from sends...\n");
				this->status = CommunicatorStatus::DISCONNECTED;
			}
		}
	}

	// Update Requests
	for (size_t i = 0; i < requests.size(); i++)
	{
		Request* tempRequest = this->requests[i];

		{
			if (tempRequest->status == RequestStatus::PENDING)
			{
				printf("pushed a sending packet from request\n");
				this->sends.push(tempRequest->sendPacket);
				tempRequest->status = RequestStatus::SENT;
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

sf::Packet Communicator::fetch(PacketProperties& properties)
{
	std::pair<sf::Packet, PacketProperties> frontPair = this->receives.front();
	this->receives.pop();
	properties = frontPair.second;
	return frontPair.first; 
}

ConnectRequest* Communicator::requestConnect(sf::Uint8 teamID)
{
	printf("connecting to ");
	std::cout << this->serverAddress.toString() << "\n";

	this->socket->setBlocking(true);

	sf::Socket::Status connectStatus = this->socket->connect(serverAddress, 2000);

	while (connectStatus != sf::Socket::Status::Done)
	{
		if (connectStatus != sf::Socket::Status::NotReady)
		{
			printf("socket error connecting to server...\n");
			return nullptr;
		}
		else
		{
			connectStatus = this->socket->connect(serverAddress, 2000);
		}
	}

	this->socket->setBlocking(false);


	printf("socket is connected to server! sending login request...\n");

	// "hello" message / login
	ConnectRequest* request = new ConnectRequest(this->getCurrentRequestID(), this->teamID, &(this->status));

	request->sendPacket << teamID;

	this->requests.emplace_back(request);

	return request;
}

ShopInformationRequest* Communicator::requestShopInformation(Point* point)
{
	ShopInformationRequest* request = new ShopInformationRequest(this->getCurrentRequestID(), point->getID(), point);

	this->requests.emplace_back(request);

	return request;
}

PurchaseRequest* Communicator::requestPurchase(Player* player, Point* point)
{
	PurchaseRequest* request = new PurchaseRequest(this->getCurrentRequestID(), point->getID(), player, point);

	this->requests.emplace_back(request);

	return request;
}

MoveRequest* Communicator::requestMove(Player* player, Point* point)
{
	MoveRequest* request = new MoveRequest(this->getCurrentRequestID(), point->getID(), player, point);

	this->requests.emplace_back(request);

	return request;
}

TeamInformationRequest* Communicator::requestTeamInformation(Player* team)
{
	TeamInformationRequest* request = new TeamInformationRequest(this->getCurrentRequestID(), team->getID(), team);

	this->requests.emplace_back(request);

	return request;
}
