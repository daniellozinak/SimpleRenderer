#version 330
	
#define MAX_LIGHTS 4
#define DIRECTIONAL 0
#define POINT 1
#define SPOT 2

out vec4 frag_colour;
in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
in float default_height;

uniform vec3 viewPosition;

const float sharpness = 25;
const vec3 lightColor = vec3(1.0);

uniform float is_selected = 1;
uniform float max_height;

uniform int lightCount;

vec3 worldNormal = ex_worldNormal;

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

//min: 60, max: 150


vec3 calculateColor()
{
	float height = default_height;

	height += max_height;

	if(height <= max_height*(1/6))
	{
		worldNormal = vec3(0,1,0);
		return vec3(50.0/255.0, 115/255.0, 168/255.0);
	}

	const float maxR = 150.0;
	const float minR = 60.0;

	float diffR = maxR-minR;

	float R = minR + ( diffR * (height/(max_height*2)) );



	return vec3(R/255.0,110.0/255.0,25.0/255.0);
}

uniform Light lights[MAX_LIGHTS];


void main () {
		vec3 viewDirection = normalize(viewPosition- ex_worldPosition.xyz);

		vec3 ambient;

		vec3 diffuse;

		float light_angle;
		for(int i = 0; i < lightCount; i++)
		{
			ambient = lights[i].ambient * lightColor;

			if(lights[i].lightType == SPOT)
			{
				
				vec3 reflectDirection =  normalize(reflect(ex_worldPosition.xyz-lights[i].position,worldNormal));
				vec3 lightDirection = normalize(lights[i].position - ex_worldPosition.xyz);

				float diffuseStrength = max(dot(lightDirection,worldNormal),0.0);	
				float specularStrength = pow(max(dot(viewDirection,reflectDirection),0.0),sharpness);

				diffuse  += lights[i].diffuse * diffuseStrength * lightColor;

				light_angle = dot(lightDirection,normalize(-lights[i].direction));

				if(light_angle > lights[i].angle)
				{
					float diff = lights[i].angle / light_angle;
					diffuse  *= diff;
				}
				else{
					diffuse = vec3(0.0);
				}
			}
			else if(lights[i].lightType == POINT)
			{
				
				vec3 reflectDirection =  normalize(reflect(ex_worldPosition.xyz-lights[i].position,worldNormal));
				vec3 lightDirection = normalize(lights[i].position - ex_worldPosition.xyz);

				float diffuseStrength = max(dot(lightDirection,worldNormal),0.0);	
				float specularStrength = pow(max(dot(viewDirection,reflectDirection),0.0),sharpness);

				diffuse  += lights[i].diffuse * diffuseStrength * lightColor;

				float lightDistance = length(lights[i].position - ex_worldPosition.xyz);
				float attenuation = 1.0/(((lights[i].quad.x)*(lightDistance*lightDistance)) + ((lights[i].quad.y)*(lightDistance)) + ((lights[i].quad.z)));
				
				diffuse  *= attenuation;
			}
			else if(lights[i].lightType == DIRECTIONAL)
			{
				vec3 reflectDirection =  normalize(reflect(ex_worldPosition.xyz-lights[i].direction,worldNormal));
				vec3 lightDirection = normalize(lights[i].direction - ex_worldPosition.xyz);

				float diffuseStrength = max(dot(lightDirection,worldNormal),0.0);	
				float specularStrength = pow(max(dot(viewDirection,reflectDirection),0.0),sharpness);

				diffuse  += lights[i].diffuse * diffuseStrength * lightColor;
			}
		}
		vec3 DAS = (diffuse + ambient) * calculateColor();

		frag_colour =  vec4(DAS,1.0);
};