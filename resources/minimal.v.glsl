#version 410
uniform mat4 mvp;
in vec3 position;
in vec3 color;
out vec4 vec_color;
void main()
{
	vec_color = vec4(color, 1);
	gl_Position = mvp * vec4(position,1);
}
