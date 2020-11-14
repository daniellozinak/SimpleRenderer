#version 330
	
#define MAX_LIGHTS 4
#define DIRECTIONAL 0
#define POINT 1
#define SPOT 2

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

uniform int lightCount;

struct Light{
	vec3 position;
	vec3 diffuse;
	vec3 ambient;
	vec3 specular;

	vec3 quad;
	float angle;
	vec3 direction;

	int lightType;
};


uniform Light lights[MAX_LIGHTS];


void main () {

		color = color *is_selected;
		vec3 viewDirection = normalize(viewPosition- ex_worldPosition.xyz);

		vec3 ambient = ambientConstant * lightColor;

		vec3 diffuse;
		vec3 specular;

		float light_angle;
		for(int i = 0; i < lightCount; i++)
		{
			vec3 reflectDirection =  normalize(reflect(ex_worldPosition.xyz-lights[i].direction,ex_worldNormal));
			vec3 lightDirection = normalize(lights[i].position - ex_worldPosition.xyz);

			float diffuseStrength = max(dot(lightDirection,ex_worldNormal),0.0);	
			float specularStrength = pow(max(dot(viewDirection,reflectDirection),0.0),sharpness);

			diffuse  += diffuseConstant * diffuseStrength * lightColor;
			specular += specularConstant  * specularStrength * lightColor;


			if(lights[i].lightType == SPOT)
			{
				light_angle = dot(lightDirection,normalize(-lights[i].direction));
				if(light_angle > lights[i].angle)
				{
					float diff = lights[i].angle / light_angle;
					diffuse  *= diff;
					//specular =  vec3(0.0);
				}
				else{
					diffuse = vec3(0.0);
					specular =  vec3(0.0);
				}
			}
			else if(lights[i].lightType == POINT)
			{
				float lightDistance = length(lights[i].position - ex_worldPosition.xyz);

				float attenuation = 1.0/(((lights[i].quad.x)*(lightDistance*lightDistance)) + ((lights[i].quad.y)*(lightDistance)) + ((lights[i].quad.z)));
				diffuse  *= attenuation;
				specular *= attenuation;
			}
			else{
				//to nothing
			}
		}
		vec3 DAS = (diffuse + ambient) * color + specular*vec3(1.0);

		frag_colour = vec4(DAS,1.0);
};