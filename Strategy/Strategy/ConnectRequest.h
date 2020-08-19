#pragma once
#include "Request.h"
class ConnectRequest :
    public Request
{
private:

    // return target
    CommunicatorStatus* communicatorStatus;

public:

    ConnectRequest();
    ConnectRequest(sf::Uint32 requestID, sf::Uint8 teamID, CommunicatorStatus* status);
    ~ConnectRequest();

    void update();

};

