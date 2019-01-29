#include <iostream>
#include <chrono>

#include "system.h"
#include "renderer.h"

int main_halt()
{
	float msPerTick = 1000.0 / 60.0;
	GameState* newInstance = new GameState;
	Window* thisGame = new Window;
	float processedTime;

	if (newInstance->reportSystemStatus)
	{
		while (newInstance->reportSystemStatus) //main loop. runs while systemStatus == 1
		{
			
			/*
			MS_PER_TICK = 1000 / 60 (TIME BETWEEN 60 FRAMES IN A SECOND)
			PROCESSED_TIME = currentTimeInMs()

			while(game is running)
				drawFrame()
				while(PROCESSED_TIME + MS_PER_TICK) < currentTimeInMs()
					updateGame()
					PROCESSED_TIME = PROCESSED_TIME + MS_PER_TICK
			*/
		}
	}
	else if (newInstance->reportSystemStatus == 0 && newInstance->reportApplicationState == 4)
	{
		//Some happy ass shit and make sure to prevent memory leaks
	}
	else
	{
		//something went wrong, check errors
	}
	std::cin.get();
}