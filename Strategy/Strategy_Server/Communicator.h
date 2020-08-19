#pragma once

#include "PacketProperties.h"

// Server communicator


class Communicator
{
private:

	// Status

	sf::Uint32 currentSendID;

	sf::Uint32 currentBroadcastID;


	// Components

	sf::TcpListener* listener;

	sf::TcpSocket* clientSockets[numTeams + 1];

	sf::SocketSelector selector;


	// Storage

	std::queue<sf::Packet> requests[numTeams + 1];

	std::queue<sf::Packet> sends[numTeams + 1];


public:

	// Constructors/Destructor

	Communicator();

	~Communicator();


	// Methods

	void update();

	bool newRequest(sf::Uint8 teamID) { return !this->requests[teamID].empty(); };
	// if there's new request from the client

	sf::Packet fetch(sf::Uint8 teamID) { return this->requests[teamID].front(); };
	//  call after calling newRequest

	void send(sf::Uint8 teamID, sf::Packet packet) { this->sends[teamID].push(packet); };

	void broadcast(sf::Packet packet) { for (size_t i = 1; i <= numTeams; i++) this->sends[i].push(packet); };
	

	// Queries


};

