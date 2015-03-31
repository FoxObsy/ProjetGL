#version 410

in vec3 position;
in vec3 vColor;

out vec3 color;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(position,1.0);
	color = vColor;
}
