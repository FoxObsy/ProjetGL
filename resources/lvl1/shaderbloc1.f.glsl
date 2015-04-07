#version 410

in vec2 uvColor;
flat in int inTarget;

out vec3 out_color;

uniform sampler2D colorMap;

void main()
{
	if(inTarget==1){	
		out_color = texture(colorMap,uvColor).xyz + vec3(0.5,0.0,0.0);
	}
	else{
		out_color = texture(colorMap,uvColor).xyz;
	}
}
