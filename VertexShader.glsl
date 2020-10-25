#version 330
layout(location=0) in vec3 vp;
layout(location=1) in vec3 vc;
out vec3 fragmentColor;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPosition;

void main () {
	  mat4 mvp =  projectionMatrix * viewMatrix * modelMatrix;
	  gl_Position = mvp * vec4(vp, 1.0);
	  fragmentColor = vc ;
}