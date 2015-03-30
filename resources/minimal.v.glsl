#version 410
uniform mat4 mvp;
in vec3 position;
out vec4 vec_color;
void main()
{
	vec_color = vec4(position, 1);
	gl_Position = mvp * vec4(position,1);
}
