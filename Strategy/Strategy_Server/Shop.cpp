#include "Shop.h"
#include "Team.h"

Shop::Shop(sf::Uint8 ID)
	:ID(ID), capital({ 0 }), basePrice({ 0 }), baseRevenue({ 0 }), moveTime({ 0 }), ownerID(0), bankrupted(false), transactionTimes(0), prevRev(0)
{
}

Shop::Shop(sf::Uint8 ID, std::array<sf::Uint32, numCapPhases> capital, std::array<sf::Uint32, numCapPhases> basePrice, std::array<sf::Uint32, numRevPhases> baseRevenue, std::array<double, numShops + 1> moveTime)
	: ID(ID), capital(capital), basePrice(basePrice), baseRevenue(baseRevenue), moveTime(moveTime), ownerID(0), bankrupted(false), transactionTimes(0), prevRev(0)
{
}

void Shop::addTag(ShopTag tag)
{
	this->tags.push_back(tag);
}


bool Shop::purchasable()
{
	if (this->transactionTimes == 0 || this->timeSinceTransaction.getElapsedTime() >= purchaseCD)
	{
		return true;
	}

	return false;
}

void Shop::transaction(sf::Uint8 newOwnerID)
{
	this->ownerID = newOwnerID;
	this->transactionTimes++;
	this->timeSinceTransaction.restart();
}
