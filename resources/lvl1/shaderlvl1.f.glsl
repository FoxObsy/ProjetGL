#version 410

in vec2 uvColor;

out vec3 out_color;

uniform sampler2D colorMap;

void main()
{
	out_color = texture(colorMap,uvColor).xyz;
}
