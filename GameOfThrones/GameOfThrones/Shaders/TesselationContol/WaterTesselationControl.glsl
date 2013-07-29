#version 330 core

layout(vertices = 3) out;
in vec3 vPosition[];

//in vec2 UV;
//in vec3 Position_worldspace;
//in vec3 Normal_cameraspace;
//in vec3 EyeDirection_cameraspace;
//in vec3 LightDirection_cameraspace;

//out vec2 UV;
//out vec3 Position_worldspace;
//out vec3 Normal_cameraspace;
//out vec3 EyeDirection_cameraspace;
//out vec3 LightDirection_cameraspace;

uniform float TessLevelInner;
uniform float TessLevelOuter;

out vec3 tcPosition[];

#define ID gl_InvocationID

void main()
{
	tcPosition[ID] = vPosition[ID];

	if (ID == 0) {
		gl_TessLevelInner[0] = TessLevelInner;
		gl_TessLevelOuter[0] = TessLevelOuter;
		gl_TessLevelOuter[1] = TessLevelOuter;
		gl_TessLevelOuter[2] = TessLevelOuter;
	}
}
