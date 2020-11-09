#version 330
	

uniform float is_selected = 1;

out vec3 frag_colour;
const vec3 color = vec3(0.1,0.2,0.7);
void main () {
      frag_colour = color;
};