#version 330
out vec4 frag_colour;
in vec3 fragmentColor;
void main () {
	frag_colour = vec4(fragmentColor, 1.0);
}