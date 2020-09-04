#pragma once

#include "Variables.h"
//#include "Server.h"

enum class GameEventType
{
	START,

	SYNCHRONIZE,

	REVENUE,

	BANKRUPT,

	NEXT_CAP_PHASE,

	NEXT_REV_PHASE,

	PRINT_LEADER,

	FINISH,
};

class GameEvent
{
protected:

	sf::Time time;

	GameEventType type;

public:

	GameEvent(int minute, int sencond, GameEventType type);

	sf::Time getTime() { return this->time; };
	GameEventType getType() { return this->type; };

	~GameEvent();

	//bool operator>(const GameEvent& other);

};

