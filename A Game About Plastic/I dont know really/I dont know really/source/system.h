#pragma once

class GameState
{
private:
	bool systemStatus; //1 represents ON state, 0 represents OFF state
	int applicationState; //0 == Loading Screen, 1 == Main Menu, 2 == In Game, 3 == Pause Menu, (OPTIONAL) 4 == Outro
public:
	bool reportSystemStatus() const; //returns systemStatus
	int reportApplicationState() const; //returns applicationState
	GameState(); //sets the class's private variables to initial values
	~GameState(); //makes sure all is closed nicely
};