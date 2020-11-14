#version 330
	
#define MAX_LIGHTS 4
out vec4 frag_colour;
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec3 viewPosition;

const float ambientConstant = 0.2;
const float diffuseConstant = 0.8;
const float specularConstant = 0.8;
const float sharpness = 25;
vec3 color = vec3(0.1,0.2,0.7);
const vec3 lightColor = vec3(1.0);

uniform float is_selected = 1;

uniform int lightCount = 1;

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

	  vec3 ambient = ambientConstant * lightColor;

	  vec3 diffuse;
	  vec3 specular;

	  for(int i = 0; i < lightCount; i ++)
	  {

		vec3 reflectDirection =  normalize(reflect(ex_worldPosition.xyz-lights[i].position,ex_worldNormal));
		vec3 lightDirection = normalize(lights[i].position - ex_worldPosition.xyz);

		float diffuseStrength = max(dot(lightDirection,ex_worldNormal),0.0);	
		float specularStrength = pow(max(dot(viewDirection,reflectDirection),0.0),sharpness);

		diffuse  += diffuseConstant * diffuseStrength * lightColor;
		specular += specularConstant  * specularStrength * lightColor;

	  }


	  vec3 DAS = (diffuse + ambient) * color + specular*vec3(1.0);
      frag_colour = vec4(DAS,1.0);
};