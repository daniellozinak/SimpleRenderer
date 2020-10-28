#version 330
	
out vec4 frag_colour;
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;

uniform vec3 lightPosition;
uniform vec3 viewPosition;

const float lightIntensity = 0.9;
const float reflectConstant = 0.6;
const float sharpness = 25;
const vec3 color = vec3(0.1,0.2,0.7);
const vec3 lightColor = vec3(1.0);

void main () {
	  vec3 viewDirection = normalize(viewPosition- ex_worldPosition.xyz);
	  vec3 lightDirection = (lightPosition - ex_worldPosition.xyz);
	  vec3 halfVector = (viewDirection + lightDirection) / (length (viewDirection + lightDirection));

	  float diffuseStrength = max(dot(lightDirection,ex_worldNormal),0.0);	

	  vec3 diffuse = diffuseStrength * lightColor;
	  vec3 ambient = lightIntensity * lightColor;

	  float specular = pow(max(dot(ex_worldNormal,halfVector),0.0),sharpness);
	  vec3 specularVector = reflectConstant  * specular * lightColor;
	  vec3 DAS = (diffuse + ambient) * color + specularVector ;
      frag_colour = vec4(DAS,1.0);
};