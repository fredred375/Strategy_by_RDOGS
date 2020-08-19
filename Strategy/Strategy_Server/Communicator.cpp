
#include "Communicator.h"

// Code for server communicator

sf::Packet& operator <<(sf::Packet& packet, const PacketProperties& t)
{
	return packet 
		<< t.ID 
		<< static_cast<INT32>(t.packetType) 
		<< static_cast<INT32>(t.subType) 
		<< static_cast<INT32>(t.requestValidity);
}

sf::Packet& operator >>(sf::Packet& packet, PacketProperties& t)
{
	sf::Int32 packetType, subType, requestValidity;
	packet
		>> t.ID
		>> packetType
		>> subType
		>> requestValidity;
	t.packetType = static_cast<PacketType>(packetType);
	t.subType = static_cast<SubType>(subType);
	t.requestValidity = static_cast<RequestValidity>(requestValidity);

	return packet;
}

Communicator::Communicator()
	: currentSendID(0), currentBroadcastID(0), listener(new sf::TcpListener)
{
	for (size_t i = 0; i <= numTeams; i++)
	{
		clientSockets[i] = nullptr;
	}

	if (this->listener->listen(port) != sf::Socket::Status::Done)
	{
		printf("listener error listening...\n");
		exit(1);
	}

	printf("listening on port %d\n", port);

	sf::IpAddress localIp = sf::IpAddress::getLocalAddress(), publicIp = sf::IpAddress::getPublicAddress();

	std::cout << "Local IP:\t" << localIp << "\nPublic IP:\t" << publicIp << "\n";

	this->selector.add(*this->listener);
}

Communicator::~Communicator()
{
	this->listener->close();
	delete this->listener;
	this->listener = nullptr;

	for (size_t i = 1; i <= numTeams; i++)
	{
		this->clientSockets[i]->disconnect();
		delete this->clientSockets[i];
		this->clientSockets[i] = nullptr;
	}
}



void Communicator::update()
{
	// send ----------------------

	for (size_t i = 1; i <= numTeams; i++)
	{
		if (clientSockets[i] != nullptr && !this->sends[i].empty()) // new sends
		{
			sf::Socket::Status status = clientSockets[i]->send(this->sends[i].front());

			switch (status)
			{

			case sf::Socket::Done:

				sends[i].pop();

				printf("sent packet to team %d\n", i);

				break;


			case sf::Socket::NotReady:

				printf("team %d is busy...\n", i);

				break;
			

			case sf::Socket::Disconnected:

				this->selector.remove(*this->clientSockets[i]);
				delete this->clientSockets[i];
				clientSockets[i] = nullptr;

				printf("team %d has disconnected...\n", i);

				break;


			case sf::Socket::Error:

				printf("error sneding packet to team %d...\n", i);

				break;


			default:

				printf("unknown error sending pacekt to team %d...", i);

				break;
			}
		}
	}


	// receive -------------------
	
	if (this->selector.wait(selectorTimeout))
	{
		if (this->selector.isReady(*this->listener)) // new client
		{
			sf::TcpSocket* newClientSocket = new sf::TcpSocket;

			if (this->listener->accept(*newClientSocket) == sf::Socket::Status::Done)
			{
				printf("accepted new connection\n");
			}
			

			sf::Packet recievePacket, sendPacket;
			PacketProperties receivePacketProperties;


			if (newClientSocket->receive(recievePacket) == sf::Socket::Status::Done)
			{
				recievePacket >> receivePacketProperties;

				PacketProperties sendPacketProperties(receivePacketProperties.ID, PacketType::RESPONSE, SubType::RESPONSE_CONNECT);
				
				// not connected
				if (receivePacketProperties.subType != SubType::REQUEST_CONNECT)
				{
					sendPacketProperties.requestValidity = RequestValidity::NOT_CONNECTED;

					sendPacket << sendPacketProperties;
					
					printf("recieved not connected request\n");
				}

				else
				{
					printf("recieved connecting request\n");
					sf::Uint8 teamID;
					recievePacket >> teamID;

					if (teamID > numTeams || teamID <= 0) // ID out of range
					{
						sendPacketProperties.requestValidity = RequestValidity::INVALID_TEAM_ID;

						sendPacket << sendPacketProperties;

						printf("invalid id\n");
					}

					else if (clientSockets[teamID] != nullptr) // reconnection
					{
						sendPacketProperties.requestValidity = RequestValidity::VALID;

						sendPacket << sendPacketProperties;

						// remove original socket
						this->selector.remove(*this->clientSockets[teamID]);
						delete this->clientSockets[teamID];

						this->selector.add(*newClientSocket);
						this->clientSockets[teamID] = newClientSocket;
						
						printf("team %d had reconnected!\n", teamID);
					}

					else // new connection
					{
						sendPacketProperties.requestValidity = RequestValidity::VALID;

						sendPacket << sendPacketProperties << teamID;

						this->selector.add(*newClientSocket);
						this->clientSockets[teamID] = newClientSocket;

						printf("team %d had joined the game!\n", teamID);
					}
				}

				newClientSocket->send(sendPacket);

			}

			else
			{
				printf("error receiving new client\n");
			}
		}

		else
		{
			for (size_t i = 1; i <= numTeams; i++)
			{
				if (selector.isReady(*this->clientSockets[i])) // recieve requests from client
				{
					sf::Packet receivePacket;

					if (this->clientSockets[i]->receive(receivePacket))
					{
						this->requests->push(receivePacket);

						printf("recieved request from team %d\n", i);
					}

					else
					{
						printf("error receiving packet from team %d\n", i);
					}
				}
			}
		}
	}
}

