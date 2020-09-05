#pragma once
#include "Variables.h"

enum class ShopTag
{
	WENZHOU = 0,

	SHIDA = 1,

	YIYIBA = 2,

	GONGGUAN = 3,

	FASTFOOD = 4,

	STARBUCKS = 5,

	CURRY = 6,

	RAMEN = 7,

	HOTPOT = 8,

	ICE = 9,

	CHAMONIX = 10,

	MALA = 11,

	numShopTags
};

class Team;

class Shop
{
private:

	// Properties

	const sf::Uint8 ID;

	std::list<ShopTag> tags;

	std::array<sf::Uint32, numCapPhases> capital;

	std::array<sf::Uint32, numCapPhases> basePrice;

	std::array<sf::Uint32, numRevPhases> baseRevenue;

	std::array<double, numShops + 1> moveTime;
	
	

	// Status

	sf::Uint8 ownerID;

	bool bankrupted;

	sf::Uint16 transactionTimes;

	sf::Clock timeSinceTransaction;


public:

	// Constructors / Destructors

	Shop(sf::Uint8 ID);

	Shop(sf::Uint8 ID, std::array<sf::Uint32, numCapPhases> capital, std::array<sf::Uint32, numCapPhases> basePrice, std::array<sf::Uint32, numRevPhases> baseRevenue, std::array<double, numShops + 1> moveTime);

	void addTag(ShopTag tag);

	// Queries

	sf::Uint8 getID() { return this->ID; };

	sf::Uint8 getOwnerID() { return this->ownerID; };

	sf::Uint32 getCapital(sf::Uint8 phase) { return this->capital[phase]; };

	sf::Uint32 getPrice(sf::Uint8 phase) { return this->basePrice[phase] * pow(1.1, transactionTimes); };

	bool getBankrupt() { return this->bankrupted; };

	sf::Uint32 getRevenue(sf::Uint8 phase) { return this->baseRevenue[phase]; };

	sf::Uint32 getPrevRevenue(sf::Uint8 phase) 
	{ 
		if (phase == 0) return 0;
		return this->baseRevenue[phase]; 
	};

	std::list<ShopTag> getTags() { return this->tags; };

	double getMoveTime(Shop* destination) { return this->moveTime[destination->getID()]; };

	sf::Uint16 getTransactionTimes() { return this->transactionTimes; };

	bool purchasable();

	void transaction(sf::Uint8 newOwnerID);

	void bankrupt() { this->bankrupted = true; };

	void revisit() { this->timeSinceTransaction.restart(); }

};

