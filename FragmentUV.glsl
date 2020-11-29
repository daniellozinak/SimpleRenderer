#version 330
out vec4 frag_colour;
uniform sampler2D textureUnitID;    
in vec2 ex_texture;
void main () {
     //frag_colour = texture(textureUnitID, ex_texture);
     frag_colour = texture(textureUnitID, ex_texture);
}