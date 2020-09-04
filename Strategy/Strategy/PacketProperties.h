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

	REQUEST_TEAM_INFORMATION,

	// sf::Uint8 teamID



	// RESPONSE -------------------------------

	RESPONSE_CONNECT,

	// sf::Uint8 teamID
	// bool 

	// [NOT_CONNECTED] 
	// (nothing)


	RESPONSE_SHOP_INFORMATION,

	// sf::Uint8 shopID,
	// sf::Uint8 owenerID,
	// sf::Uint32 capital, 
	// sf::Uint32 price,
	// sf::Uint32 prevRevenue,
	// sf::Uint16 transactionTimes
	// sf::Uint16 duration

	// [INVALID_SHOP_ID]
	// (nothing)



	RESPONSE_SHOP_PURCHASE,

	// sf::Uint8 shopID,
	// sf::Uint8 previousOwnerID,
	// sf::Uint32 cost,
	// sf::Int32 cashRemain
	// sf::Int32 capital

	// [INSUFFICIENT_CASH]
	// sf::Uint8 shopID,
	// sf::Uint32 shortage

	// [FREQUENT_PURCHASE]
	// sf::Uint8 shopID,
	// sf::Time availableTime

	// [ALREADY_OWNED]
	// sf::Uint8 shopID

	// [NOT_ON_SITE]
	// sf::Uint8 shopID



	RESPONSE_MOVE,

	// sf::Uint8 shopID
	// sf::Uint16 duration

	// [MOVING]
	// (nothing)

	RESPONSE_TEAM_INFORMATION,

	// sf::Uint8 teamID
	// sf::Int32 cash
	// sf::Int32 capital
	// sf::Uint16 numShopsOwned (not include bankrupted ones)
	// sf::Uint8 ownedShopsID * numShopsOwned 
	// sf::Uint8 visitingShopID
	// sf::Uint8 prevVisitingShopID
	// bool moving
	// sf::Uint16 duration (as senconds)


	// BROADCAST ----------------------------

	BROADCAST_START,

	BROADCAST_GAME_TIME,

	// sf::Uint32 currentGameTime


	//BROADCAST_REVENUE,


	BROADCAST_BANKRUPT,

	// sf::Uint8 shopID


	BROADCAST_TRANSACTION,

	// sf::Uint8 shopID,
	// sf::Uint8 purchasingTeamID,
	// sf::Uint8 sellingTeamID (0 for none)
	// sf::Uint32 price


	BROADCAST_MOVE,

	// sf::Uint8 teamID
	// sf::Uint8 from
	// sf::Uint8 to
	// sf::Uint16 duration

	SEND_PRICE_UPDATE,

	// sf::Int32 capital


	// SEND ---------------------------------

	SEND_PLAYER_INFORMATION, // sent on reconnecting initialization

							 // sf::Int32 cash
							 // sf::Int32 capital
							 // sf::Uint16 numShopsOwned
							 // sf::Uint8 ownedShopsID * numShopsOwned
							 // sf::Uint8 visitingShopID
							 // sf::Uint8 prevVisitingShopID
							 // bool moving
							 // sf::Uint16 duration (as seconds) (0 if not moving)

							 SEND_MOVE, // sent on reconnecting initialization
										// sf::Uint8 teamID
										// sf::Uint8 from
										// sf::Uint8 to
										// sf::Uint16 duration

										SEND_SELL,

										// sf::Uint8 shopID,
										// sf::Uint8 purchasingTeamID,
										// sf::Uint32 income
										// sf::Int32 cashBalance
										// sf::Int32 capital

										SEND_REVENUE,

										// sf::Int32 amount
										// std::vector<sf::Int32> byShop
										// sf::Uint32 cashBalance

										SEND_BANKRUPT,

										// sf::Uint8 shopID
										// sf::Int32 capital

										SEND_ERROR,

										// sf::String line1
										// sf::String line2
										// sf::String line3
										// sf::String line4
										// sf::String line5
};

enum class RequestValidity
{
	NA, // if this packet is not a return packet

	VALID,

	INVALID_SHOP_ID,

	INSUFFICIENT_CASH,

	NOT_CONNECTED,

	INVALID_TEAM_ID,

	FREQUENT_PURCHASE,

	ALREADY_OWNED,

	NOT_ON_SITE,

	MOVING,

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