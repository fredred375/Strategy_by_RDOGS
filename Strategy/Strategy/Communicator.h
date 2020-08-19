#pragma once

#include "ConnectRequest.h"

// Client communicator



class Communicator
{
	// Properties

	sf::Uint8 teamID = 1;


	// Status

	CommunicatorStatus status;

	sf::Uint32 currentRequestID;

	sf::IpAddress serverAddress;


	// Component

	sf::TcpSocket* socket;


	// Connect

	bool requested = false;

	ConnectRequest* connectRequest;

	sf::Uint8 returnTeamID;



	// Storage

	std::queue<sf::Packet> receives;

	std::queue<sf::Packet> sends;

	std::vector<Request*> requests;


	// Methods

	sf::Uint32 getCurrentRequestID() { return this->currentRequestID++; };


public:

	// Constructors/Destructors

	Communicator();

	Communicator(std::string serverAddress);

	~Communicator();


	// Methods



	CommunicatorStatus getStatus() { return this->status; };

	void setServerAddress(std::string serverAddress) { this->serverAddress = sf::IpAddress(serverAddress); };

	void update(); // send/receive

	sf::Packet fetch() { return this->receives.front(); };

	void send(sf::Packet packet) { this->sends.push(packet); };


	// Requests

	ConnectRequest* requestConnect(sf::Uint8 teamID); // returns nullptr if the socket failed to connect


};

