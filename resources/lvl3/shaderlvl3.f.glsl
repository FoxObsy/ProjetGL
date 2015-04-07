#version 410

in vec2 uv;
in vec3 normal;		//CameraSpace
in vec3 lightdirn;	//CameraSpace

uniform sampler2D colorMap;
uniform vec3 lightcolor;

//material --------------------------------------------------------
vec3 ambient = vec3(0.5,0.5,0.5);
vec3 diffuse = vec3(1,1,1);

out vec3 fragColor;


/*-- LAMBERT ------------------------------------------------------------------------------------*/

vec3 ComputeLightLambert(const in vec3 lightdirn, const in vec3 lightcolor, const in vec3 normal, const in vec3 mydiffuse)
{
    vec3 lambert=max(0,dot(lightdirn,normal))*mydiffuse*lightcolor;
    return lambert;
}


void main()
{
  vec3 normlightdirn = normalize(lightdirn);

  vec3 fragNormal = normalize(normal);

  vec3 lambert = ComputeLightLambert(normlightdirn, lightcolor, fragNormal, diffuse);

  fragColor= vec3(ambient*texture(colorMap,uv).rgb+lambert*texture(colorMap,uv).rgb);
}
