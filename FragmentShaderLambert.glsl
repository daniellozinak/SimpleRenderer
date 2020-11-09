#version 330

out vec4 frag_colour;
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
uniform vec3 lightPosition;
uniform vec3 viewPosition;
const float lightIntensity = 0.5;
const vec3 color = vec3(0.1,0.2,0.7);
const vec3 lightColor = vec3(0.3,0.3,0.3);

uniform float is_selected = 1;

void main() {

	vec3 lightDirection = (lightPosition - ex_worldPosition.xyz);
	float light_vertexDot = max(dot(lightDirection, normalize(ex_worldNormal)), 0.0);


	vec3 diffuse = light_vertexDot * lightColor;
	vec3 ambient = lightIntensity * lightColor;


	vec3 result = (diffuse + ambient) * color;
	frag_colour = vec4(result, 1.0);
}