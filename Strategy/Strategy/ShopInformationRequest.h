#pragma once
#include "Request.h"
class ShopInformationRequest :
    public Request
{
private:

    // return target
    Point* point;

public:
    ShopInformationRequest(sf::Uint32 requestID, sf::Uint8 shopID, Point* point);
    ~ShopInformationRequest();

    void update();
};

