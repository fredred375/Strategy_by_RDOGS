#pragma once

#include "Variables.h"

enum class PacketType
{
	NA,

	REQUEST,

	RESPONSE,

	BROADCAST,

	SEND
};

enum class SubType
{
	NA,

	// REQUEST -------------------------------- 

	REQUEST_CONNECT,

	// sf::Uint8 teamID


	REQUEST_SHOP_INFORMATION, 

	// sf::Uint8 shopID


	REQUEST_SHOP_PURCHASE,

	// sf::Uint8 shopID


	REQUEST_MOVE,

	// sf::Uint8 shopID



	// RESPONSE -------------------------------

	RESPONSE_CONNECT,

	// sf::Uint8 teamID

	// [NOT_CONNECTED] 
	// (nothing)


	RESPONSE_SHOP_INFORMATION,

	// sf::Uint8 shopID,
	// sf::Uint8 ownerID,
	// bool bankrupt, 
	// sf::Uint32 capital, 
	// sf::Uint32 price

	// [INVALID_SHOP_ID]
	// (nothing)



	RESPONSE_SHOP_PURCHASE,

	// sf::Uint8 shopID,
	// sf::Uint8 previousOwnerID,
	// sf::Uint32 cost,
	// sf::Uint32 remainingCash

	// [INSUFFICIENT_CASH]
	// sf::Uint8 shopID,
	// sf::Uint32 shortage




	// BROADCAST ----------------------------

	BROADCAST_BANKRUPT,


	// SEND ---------------------------------

};

enum class RequestValidity
{
	NA, // if this packet is not a return packet

	VALID,

	INVALID_SHOP_ID,

	INSUFFICIENT_CASH,

	NOT_CONNECTED,

	INVALID_TEAM_ID,

	OTHER_ERROR,
};

struct PacketProperties
{
	sf::Uint32 ID; 
	// send and request shares same ID

	PacketType packetType;

	SubType subType;

	RequestValidity requestValidity;


	// Constructors

	PacketProperties()
		:ID(0), packetType(PacketType::NA), subType(SubType::NA), requestValidity(RequestValidity::NA)
	{};

	PacketProperties(const PacketProperties& p2)
		:ID(p2.ID), packetType(p2.packetType), subType(p2.subType), requestValidity(p2.requestValidity)
	{}

	PacketProperties(sf::Uint32 ID, PacketType packetType, SubType subType)
		: ID(ID), packetType(packetType), subType(subType), requestValidity(RequestValidity::NA)
	{};

	PacketProperties(sf::Uint32 ID, PacketType packetType, SubType subType, RequestValidity requestValidity)
		: ID(ID), packetType(packetType), subType(subType), requestValidity(requestValidity)
	{};
};
