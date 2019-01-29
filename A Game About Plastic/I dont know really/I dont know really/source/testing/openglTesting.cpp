#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "renderer.h"

#include "indexBuffer.h"
#include "vertexBuffer.h"
#include "vertexArray.h"

//UNIFORMS GET DATA FROM CPU TO SHADER WTF WHY AM I DOING THIS HELP

		//vertex - point on your geometry(can include anything)
		//we need to tell openGL what is in he memory (buffer, which is basically a block of memory in the gpu)
		//here we make the buffer object for the shader, instead of unsigned int I could use GLuint, but I dont feel like doing it all with their variable types


struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath) //sets up the shader source code
{
	std::fstream stream(filepath);
	
	enum class ShaderType
	{
		NONE = -1, VERTEX = 0, FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2]; //one for the vertex shader, and the other for the fragment shader
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos) //set vertex mode
				type = ShaderType::VERTEX;

			else if (line.find("fragment") != std::string::npos) //set fragment mode
				type = ShaderType::FRAGMENT;
		}
		else
		{
			ss[(int)type] << line << "\n"; //using the numbers from the ShaderType class we avoid needless waste of code
		}
	}
	return { ss[0].str(), ss[1].str() };
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	//error handling
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char)); //alloca - allocate dinamically on the stack (from C)
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile "<< (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	
	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs); //since shaders were already linked, we can safely delete em
	glDeleteShader(fs);

	return program;
}

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	int windowWidth = 800, windowHeight = 600;

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	window = glfwCreateWindow(windowWidth, windowHeight, "anime movies are the only source of quality", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
	{
		float positions[] = {
			-0.5f, -0.5f, //0
			 0.5f, -0.5f, //1
			 0.5f,  0.5f, //2
			-0.5f,  0.5f  //3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		unsigned int vao;
		GLCall(glGenVertexArrays(1, &vao));
		GLCall(glBindVertexArray(vao));

		VertexArray va;
		VertexBuffer vb(positions, 4 * 2 * sizeof(float));
		
		VertexBufferLayout layout;
		layout.push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		ShaderProgramSource source = ParseShader("source/res/shaders/basic.shader");

		unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
		GLCall(glUseProgram(shader));

		//GLCall(int location = glGetUniformLocation(shader, "u_Color"));
		//ASSERT(location != -1);
		//GLCall(glUniform4f(location, 0.8f, 0.3f, 0.8f, 1.0f));

		GLCall(glBindVertexArray(0));
		GLCall(glUseProgram(0));
		GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

		float r = 0.0f;
		float increment = 0.05f;

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			GLCall(glClear(GL_COLOR_BUFFER_BIT));

			GLCall(glUseProgram(shader));

			va.Bind();
			ib.Bind();

			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

			if (r > 1.0f)
				increment = -0.05f;
			else if (r < 0.0f)
				increment = 0.05f;	

			r += increment;

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		glDeleteProgram(shader);
	}
	glfwTerminate();
	return 0;
}