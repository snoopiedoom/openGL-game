#include "system.h"

GameState::GameState()
{
	systemStatus = 1;
	applicationState = 0;
}

GameState::~GameState()
{
	systemStatus = 0;
	applicationState = 4;
}

bool GameState::reportSystemStatus() const
{
	return systemStatus;
}

int GameState::reportApplicationState() const
{
	return applicationState;
}