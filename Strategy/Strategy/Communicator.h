#pragma once

#include "ConnectRequest.h"
#include "ShopInformationRequest.h"
#include "PurchaseRequest.h"
#include "MoveRequest.h"
#include "TeamInformationRequest.h"

// Client communicator

class Communicator
{
	// Properties

	sf::Uint8 teamID;

	sf::Uint16 sendPort = 2000;


	// Status

	CommunicatorStatus status;

	sf::Uint32 currentRequestID;

	sf::IpAddress serverAddress;

	sf::Uint16 failCount = 0;


	// Component

	sf::TcpSocket* socket;


	// Connect

	bool requested = false;

	ConnectRequest* connectRequest;

	sf::Uint8 returnTeamID;



	// Storage

	std::queue<std::pair<sf::Packet, PacketProperties>> receives;

	std::queue<sf::Packet> sends;

	std::vector<Request*> requests;


	// Methods

	sf::Uint32 getCurrentRequestID() { return this->currentRequestID++; };
	
	void send(sf::Packet packet) { this->sends.push(packet); };


public:

	// Constructors/Destructors

	Communicator();

	Communicator(std::string serverAddress, sf::Uint8 teamID);

	~Communicator();


	// Methods

	CommunicatorStatus getStatus() { return this->status; };

	void setServerAddress(std::string serverAddress) { this->serverAddress = sf::IpAddress(serverAddress); };

	void update(); // send/receive
	

	// Receives

	bool newReceives() { return !this->receives.empty(); };

	sf::Packet fetch(PacketProperties& properties);


	// Requests

	ConnectRequest* requestConnect(sf::Uint8 teamID); // returns nullptr if the socket failed to connect

	ShopInformationRequest* requestShopInformation(Point* point);

	PurchaseRequest* requestPurchase(Player* player, Point* point);
	
	MoveRequest* requestMove(Player* player, Point* point);

	TeamInformationRequest* requestTeamInformation(Player* team);
};

