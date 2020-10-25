#version 330

out vec4 frag_colour;
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
uniform vec3 lightPosition;
uniform vec3 viewPosition;
const float lightIntensity = 0.5;
const vec3 color = vec3(1.0, 0.0, 0.0);
const vec3 lightColor = vec3(1.0,0.2,0.0);

void main() {

	float light_vertexDot = max(dot(normalize(lightPosition - ex_worldPosition.xyz), normalize(ex_worldNormal)), 0.0);


	vec3 diffuse = light_vertexDot * lightColor;
	vec3 ambient = lightIntensity * lightColor;


	vec3 result = (diffuse + ambient) * color;
	frag_colour = vec4(result, 1.0);
}