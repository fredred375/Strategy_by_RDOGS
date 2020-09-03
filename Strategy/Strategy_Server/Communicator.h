#pragma once

#include "PacketProperties.h"

// Server communicator


class Communicator
{

private:

	// Status

	sf::Uint32 currentSendID;

	sf::Uint32 currentBroadcastID;




	// Link

	sf::Clock& gameTime;


	// Components

	sf::TcpListener* listener;

	bool loggedIn[numTeams + 1] = { false };

	sf::TcpSocket* clientSockets[numTeams + 1];

	sf::SocketSelector selector;


	// Storage

	std::queue<sf::Packet> requests[numTeams + 1];

	std::queue<sf::Packet> sends[numTeams + 1];


	// Methods

	void removeSocket(sf::Uint8 id);

	void print(std::string cat, std::string message);

	


public:


	std::array<bool, numTeams + 1> clientUninitialized;


	// Constructors/Destructor

	Communicator(sf::Clock& gameTime);

	~Communicator();

	// Queries

	bool newRequest(sf::Uint8 teamID) { return !this->requests[teamID].empty(); };
	// if there's new request from the client


	// Methods

	void update();

	void fetch(sf::Uint8 teamID, sf::Packet& packet) 
	{
		packet = this->requests[teamID].front();
		this->requests[teamID].pop();
	};
	//  call after calling newRequest

	void send(sf::Uint8 teamID, sf::Packet packet) { this->sends[teamID].push(packet); };

	void broadcast(sf::Packet packet) { for (size_t i = 1; i <= numTeams; i++) this->sends[i].push(packet); };


	sf::Uint32 getCurrentSendID() { return this->currentSendID++; };

	sf::Uint32 getCurrentBroadcastID() { return this->currentBroadcastID++; };
};

