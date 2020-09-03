#include "Request.h"



Request::Request()
	: status(RequestStatus::PENDING), sendProperties(PacketProperties()), sendPacket(sf::Packet()), timeout(requestTimeout)
{
}

Request::Request(PacketProperties properties)
	: status(RequestStatus::PENDING), sendProperties(properties), sendPacket(sf::Packet()), timeout(requestTimeout)
{
	this->sendPacket << sendProperties;
}

Request::Request(PacketProperties properties, sf::Time timeout)
	: status(RequestStatus::PENDING), sendProperties(properties), sendPacket(sf::Packet()), timeout(timeout)
{
	this->sendPacket << sendProperties;
}

Request::~Request()
{
	if (this->status == RequestStatus::RESPONDED)
	{
		printf("Request responed!\n");
	}
	else
	{
		printf("Request timeout...\n");
	}
}

void Request::update()
{
	// check timeout

	if (this->clock.getElapsedTime() > this->timeout && this->status != RequestStatus::RESPONDED)
	{
		this->status = RequestStatus::TIMEOUT;
	}
}


sf::Packet& operator <<(sf::Packet& packet, const PacketProperties& t)
{

//	std::cout << static_cast<INT32>(t.packetType) << " " << static_cast<INT32>(t.subType) << " " << static_cast<INT32>(t.requestValidity) << std::endl;

	return packet 
		<< t.ID 
		<< static_cast<INT32>(t.packetType) 
		<< static_cast<INT32>(t.subType) 
		<< static_cast<INT32>(t.requestValidity);
}


sf::Packet& operator >>(sf::Packet& packet, PacketProperties& t)
{
	INT32 packetType, subType, requestValidity;
	packet
		>> t.ID
		>> packetType
		>> subType
		>> requestValidity;

//	std::cout << t.ID << " " << packetType << " " << subType << " " << requestValidity <<  std::endl;


	t.packetType = static_cast<PacketType>(packetType);
	t.subType = static_cast<SubType>(subType);
	t.requestValidity = static_cast<RequestValidity>(requestValidity);

	return packet;
}


//sf::Packet& operator >>(sf::Packet& packet, PacketType& t)
//{
//	return 
//}