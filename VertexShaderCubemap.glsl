#version 330

layout(location=0) in vec3 vertexPosition;
layout(location=1) in vec3 vertexNormal;
layout(location=2) in vec2 vertexTexture;
out vec4 ex_worldPosition;
out vec3 ex_worldNormal;
out vec3 ex_texture;
out float default_height;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
vec3 diffuse = vec3(1.0,1.0,1.0);

void main () {
	  mat4 mvp =  projectionMatrix * viewMatrix * modelMatrix;
      gl_Position = mvp * vec4(vertexPosition, 1.0);
      default_height = vertexPosition.y;
      ex_worldPosition = modelMatrix * vec4(vertexPosition,1.0);
      ex_worldNormal = normalize(mat3(transpose(inverse(modelMatrix)))* vertexNormal);
      ex_texture = vertexPosition;
};