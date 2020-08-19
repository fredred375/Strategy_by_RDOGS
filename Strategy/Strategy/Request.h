#pragma once

#include "PacketProperties.h"

class Communicator;

enum class RequestStatus
{
	NA,

	PENDING, // not yet sent

	SENT, // sent (entered buffer)...

	RESPONDED, // response received

	TIMEOUT // timeout exceeded
};

class Request
{
	friend Communicator;

protected:

	// Properties

	RequestStatus status;

	sf::Clock clock;

	sf::Time timeout;

	PacketProperties sendProperties, receiveProperties;


	// Components

	sf::Packet sendPacket, receivePacket;


	// Setter

	//void setReturnPacket(sf::Packet);


public:

	// Constructors/Destruector

	Request();

	Request(PacketProperties properties);
	
	Request(PacketProperties properties, sf::Time timeout);

	virtual ~Request();


	// Update

	virtual void update();


	// Queries

	RequestStatus getStatus() { return this->status; };

	sf::Time getElapsedTime() { return this->clock.getElapsedTime(); };

	sf::Packet getResponsePacket() { return this->receivePacket; };


	

};

sf::Packet& operator <<(sf::Packet& packet, const PacketProperties& t);

sf::Packet& operator >>(sf::Packet& packet, PacketProperties& t);