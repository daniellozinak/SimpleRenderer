#version 330

#define MAX_LIGHTS 4

out vec4 frag_colour;
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

const float ambientConstant = 0.8;
const float diffuseConstant = 0.8;
const float specularConstant = 0.8;
const float sharpness = 75;
vec3 color = vec3(0.1,0.2,0.7);
vec3 lightColor = vec3(1.0);

uniform float is_selected = 1;

int lightCount = 0;

struct Light{
	vec3 position;
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;
};


uniform Light lights[MAX_LIGHTS];

void main () {

	  color = color *is_selected;

	  vec3 viewDirection = normalize(viewPosition- ex_worldPosition.xyz);
	  vec3 lightDirection = normalize(lightPosition - ex_worldPosition.xyz);
	  vec3 halfVector = (viewDirection + lightDirection) / (length (viewDirection + lightDirection));

	  float diffuseStrength = max(dot(lightDirection,ex_worldNormal),0.0);	

	  vec3 diffuse = diffuseConstant * diffuseStrength * lightColor;
	  vec3 ambient = ambientConstant * lightColor;

	  float specular = pow(max(dot(ex_worldNormal,halfVector),0.0),sharpness);
	  vec3 specularVector = specularConstant  * specular * lightColor;

	  vec3 DAS = (diffuse + ambient) * color + specularVector ;
      frag_colour = vec4(DAS,1.0);
};