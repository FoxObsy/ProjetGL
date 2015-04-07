#version 410

in vec3 position;
in vec2 uv;

out vec2 uvColor;

uniform mat4 MVP;

void main()
{
	gl_Position = MVP * vec4(position,1.0);
	uvColor = uv;
}
