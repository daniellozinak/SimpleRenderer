
















#version 330 core
layout(location=0) in vec3 vertexPosition;

out vec3 TexCoors;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	TexCoors = vertexPosition;
	vec4 pos = projectionMatrix * viewMatrix * modelMatrix *  vec4(vertexPosition,1.0);
	gl_Position = pos.xyww;
}