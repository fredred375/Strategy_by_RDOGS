#pragma once
#include "Request.h"
class TeamInformationRequest :
    public Request
{
private:

    // return target
    Player* team;

public:
    TeamInformationRequest(sf::Uint32 requestID, sf::Uint8 teamID, Player* team);
    ~TeamInformationRequest();

    void update();
};

