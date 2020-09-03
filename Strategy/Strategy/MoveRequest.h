#pragma once
#include "Request.h"
class MoveRequest :
    public Request
{
private:

    // return target
    Player* player;
    Point* point;

public:
    MoveRequest(sf::Uint32 requestID, sf::Uint8 shopID, Player* player, Point* point);
    ~MoveRequest();

    void update();
};

