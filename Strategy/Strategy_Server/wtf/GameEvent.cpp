#include "GameEvent.h"

GameEvent::GameEvent(int minute, int seconds, GameEventType type)
	: time(sf::seconds(60 * minute + seconds)), type(type)
{
}

GameEvent::~GameEvent()
{
}
