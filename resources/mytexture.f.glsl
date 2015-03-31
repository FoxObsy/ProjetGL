#version 410

in vec2 uvColor;
flat in int instance;

out vec3 out_color;

uniform sampler2D colorMap;
uniform int selected;

void main()
{
	if(instance == selected){	
		out_color = texture(colorMap,uvColor).xyz + vec3(0.3,0.0,0.0);
	}
	else{
		out_color = texture(colorMap,uvColor).xyz;
	}
}
