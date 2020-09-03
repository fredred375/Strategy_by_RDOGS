
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

void Communicator::removeSocket(sf::Uint8 id)
{
	this->print("SCKT", "Team " + std::to_string(id) + " has disconnected...");
	this->selector.remove(*this->clientSockets[id]);
	delete this->clientSockets[id];
	clientSockets[id] = nullptr;
}

void Communicator::print(std::string cat, std::string message)
{
	short seconds = static_cast<short>(this->gameTime.getElapsedTime().asSeconds());
	short minutes = seconds / 60;
	seconds %= 60;

	std::string secondStr, minuteStr;

	secondStr = (seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds));
	minuteStr = (minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes));

	printf("[");
	printf("%s:%s", minuteStr.c_str(), secondStr.c_str());
	printf("]\t[");
	printf(cat.c_str());
	printf("]\t");
	printf(message.c_str());
	printf("\n");
}

Communicator::Communicator(sf::Clock& gameTime)
	: currentSendID(0), currentBroadcastID(0), listener(new sf::TcpListener), gameTime(gameTime), clientUninitialized(std::array<bool, numTeams + 1>({ false }))
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

	this->print("LSTN", "Listening on port" + std::to_string(port));

	sf::IpAddress localIp = sf::IpAddress::getLocalAddress(), publicIp = sf::IpAddress::getPublicAddress();
	
	this->print("LSTN", "Local IP:\t" + localIp.toString());
	this->print("LSTN", "Public IP:\t" + publicIp.toString());

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

				this->print("SEND", "Sent packet to team " + std::to_string(i) + " !");

				break;


			case sf::Socket::NotReady:

				this->print("SEND", "Error sending packet to team " + std::to_string(i) + ": NotReady...");

				break;
			

			case sf::Socket::Disconnected:

				this->print("SEND", "Error sending packet to team " + std::to_string(i) + ": Disconnected...");

				this->removeSocket(i);

				break;


			case sf::Socket::Error:

				this->print("SEND", "Error sending packet to team " + std::to_string(i) + "...");

				break;


			default:

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
				this->print("LSTN", "Accepted new connection!");
			}
			

			sf::Packet recievePacket, sendPacket;
			PacketProperties receivePacketProperties, sendPacketProperties;

			sf::Socket::Status status = newClientSocket->receive(recievePacket);

			switch (status)
			{
			case sf::Socket::Done:

				recievePacket >> receivePacketProperties;

				sendPacketProperties = PacketProperties(receivePacketProperties.ID, PacketType::RESPONSE, SubType::RESPONSE_CONNECT);

				// not connected
				if (receivePacketProperties.subType != SubType::REQUEST_CONNECT)
				{
					sendPacketProperties.requestValidity = RequestValidity::NOT_CONNECTED;

					sendPacket << sendPacketProperties;

					this->print("LSTN", "Recieved request from not logged in client...");
				}

				else
				{
					this->print("LSTN", "Accepted connecting request!");
					sf::Uint8 teamID;
					recievePacket >> teamID;
					
					// ID out of range
					if (teamID > numTeams || teamID <= 0) 
					{
						sendPacketProperties.requestValidity = RequestValidity::INVALID_TEAM_ID;

						sendPacket << sendPacketProperties;

						this->print("RQST", "CONNECT: Invalid team ID...");
					}

					// reconnection
					else if (loggedIn[teamID]) 
					{
						sendPacketProperties.requestValidity = RequestValidity::VALID;

						sendPacket << sendPacketProperties;

						// remove original socket
						/*this->selector.remove(*this->clientSockets[teamID]);
						delete this->clientSockets[teamID];*/

						this->selector.add(*newClientSocket);
						this->clientSockets[teamID] = newClientSocket;

						this->clientUninitialized[teamID] = true;

						this->print("RQST", "CONNECT: Team " + std::to_string(teamID) + " has rejoined!");
					}

					// new connection
					else 
					{
						loggedIn[teamID] = true;

						sendPacketProperties.requestValidity = RequestValidity::VALID;

						sendPacket << sendPacketProperties << teamID;

						this->selector.add(*newClientSocket);
						this->clientSockets[teamID] = newClientSocket;

						this->clientUninitialized[teamID] = true;

						this->print("RQST", "CONNECT: Team " + std::to_string(teamID) + " has joined!");
					}
				}

				newClientSocket->send(sendPacket);

				break;


			case sf::Socket::NotReady:

				this->print("LSTN", "Error receiving new client: NotReady...");

				break;


			case sf::Socket::Disconnected:

				this->print("LSTN", "Error receiving new client: Disconnected...");

				break;


			case sf::Socket::Error:

				this->print("LSTN", "Error receiving new client...");

				break;


			default:

				break;
			}

		}

		else
		{
			for (size_t i = 1; i <= numTeams; i++)
			{
				if (this->clientSockets[i] != nullptr) // recieve requests from client
				{
					if (selector.isReady(*this->clientSockets[i]))
					{
						sf::Packet receivePacket;

						sf::Socket::Status receiveStatus = this->clientSockets[i]->receive(receivePacket);

						switch (receiveStatus)
						{
						case sf::Socket::Done:

							this->requests[i].push(receivePacket);

							this->print("RCEV", "Recieved request from team " + std::to_string(i));

							break;


						case sf::Socket::Disconnected:

							this->print("RCEV", "Error sending packet to team " + std::to_string(i) + ": Disconnected...");

							this->removeSocket(i);

							break;


						case sf::Socket::Error:

							this->print("RCEV", "Error sending packet to team " + std::to_string(i) + "...");

							break;


						default:
							break;
						}
					}
				}
			}
		}
	}
}