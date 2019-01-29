#include "renderer.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

Window::Window()
{
	windowStartup(x,y);
}

int Window::windowStartup(const int& x, const int& y)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(y, x, "At least it's better than nothing", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;
	else std::cout << glGetString(GL_VERSION) << std::endl;
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}

void drawFrame()
{

}

Window::~Window()
{

}