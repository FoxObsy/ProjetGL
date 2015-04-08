#version 410

in vec2 uv;
in vec3 normal;		//CameraSpace
in vec3 eyedirn;	//CameraSpace
in vec3 lightdirn;	//CameraSpace
flat in int inTarget;

uniform sampler2D colorMap;
uniform vec3 lightcolor;

//material --------------------------------------------------------
vec3 ambient = vec3(0.5,0.5,0.5);
vec3 diffuse = vec3(1,1,1);
vec3 specular = vec3(1,1,1);
float myshininess=80;

out vec3 fragColor;


/*-- LAMBERT ------------------------------------------------------------------------------------*/

vec3 ComputeLightLambert(const in vec3 lightdirn, const in vec3 lightcolor, const in vec3 normal, const in vec3 mydiffuse)
{
    vec3 lambert=max(0,dot(lightdirn,normal))*mydiffuse*lightcolor;
    return lambert;
}

/*-- SPECULAR -----------------------------------------------------------------------------------*/

vec3 ComputeLightSpecular (const in vec3 lightdirn, const in vec3 lightcolor, const in vec3 normal, const in vec3 eyedirn, const in vec3 myspecular, const in float myshininess)
{
    vec3 phong = pow(clamp(dot(reflect(-lightdirn,normal),normalize(eyedirn)),0,1),myshininess)*myspecular*lightcolor; 
    return phong;
}


void main()
{

  vec3 out_color;
  if(inTarget==1){	
	out_color = texture(colorMap,uv).xyz + vec3(0.3,0.3,0.0);
  }
  else{
	out_color = texture(colorMap,uv).xyz;
  }

  vec3 normlightdirn = normalize(lightdirn);

  vec3 fragNormal = normalize(normal);

  vec3 lambert = ComputeLightLambert(normlightdirn, lightcolor, fragNormal, diffuse);

  vec3 phong= ComputeLightSpecular(normlightdirn, lightcolor, fragNormal, eyedirn, specular, myshininess);

  fragColor= vec3(ambient*out_color+lambert*out_color+phong);
  //fragColor= vec3(ambient*texture(colorMap,uv).rgb+lambert*texture(colorMap,uv).rgb+phong);

}
