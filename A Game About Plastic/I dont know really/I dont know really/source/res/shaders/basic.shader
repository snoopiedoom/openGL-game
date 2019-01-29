#shader vertex
#version 140 core

in vec3 in_Position;
in vec3 in_Color;
out vec3 ex_Color;

void main()
{
	gl_Position = vec4(in_Position, 1.0);
	ex_Color = in_Color;
}

#shader fragment
#version 140 core

in vec3 ex_Color;
out vec4 out_Color;

void main()
{
	out_Color = vec4(0.2, 0.3, 0.8, 1.0);
}