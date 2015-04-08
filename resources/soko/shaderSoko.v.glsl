#version 410

in vec3 vert_position; 	//ModelSpace
in vec2 vert_uv;
in vec3 vert_normal;	//ModelSpace

out vec2 uv;
out vec3 normal;	//CameraSpace
out vec3 eyedirn;	//CameraSpace
out vec3 lightdirn;	//CameraSpace

uniform mat4 MVP;
uniform mat4 M;
uniform mat4 V;
uniform vec3 LightPosition;	//WorldSpace


void main()
{
	gl_Position = MVP * vec4(vert_position,1.0);

    	vec3 vert_position_cameraspace = ( V * M * vec4(vert_position,1)).xyz;
    	eyedirn = vec3(0,0,0) - vert_position_cameraspace;

   	vec3 LightPosition_cameraspace = ( V * vec4(LightPosition,1)).xyz;
    	lightdirn = LightPosition_cameraspace + eyedirn;

	normal = ( V * M * vec4(vert_normal,0)).xyz;

	uv = vert_uv;
	
}
