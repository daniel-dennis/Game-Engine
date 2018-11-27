#version 330

in vec2 texture_coord;

in vec3 frag_viewer_position;
in vec3 frag_light_position;
in vec3 frag_normals;
in vec3 frag_positions;

in vec3 frag_light_colour;

out vec4 frag_colour;

uniform sampler2D tex;



void main()
{
    frag_colour = texture(tex, texture_coord);
}