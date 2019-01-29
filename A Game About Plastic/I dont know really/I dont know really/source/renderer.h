#pragma once

class Window
{
private:
	int x, y;
public:
	int windowStartup(const int&, const int&);
	void drawFrame();
	Window(); //Calls the window setup
	~Window(); //dunno yet
};