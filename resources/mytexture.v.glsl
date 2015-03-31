#version 410

in vec3 position;
in vec2 uv;

out vec2 uvColor;
flat out int instance;

uniform mat4 MVP;
uniform vec3 transl[25];

void main()
{
	instance = gl_InstanceID;
	gl_Position = MVP * vec4(position + transl[gl_InstanceID],1.0);
	uvColor = uv;
}
