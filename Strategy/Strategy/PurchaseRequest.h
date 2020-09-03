#pragma once
#include "Request.h"
class PurchaseRequest :
    public Request
{
private:

    // return target
    Player* player;
    Point* point;

public:
    PurchaseRequest(sf::Uint32 requestID, sf::Uint8 shopID, Player* player, Point* point);
    ~PurchaseRequest();

    void update();
};

