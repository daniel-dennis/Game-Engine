#version 330

in vec3 vertex_position;
in vec3 vertex_normals;
in vec2 texture;

out vec2 texture_coord;

out vec3 frag_normals;
out vec3 frag_positions;
out vec3 frag_light_position;
out vec3 frag_viewer_position;
out vec3 frag_light_colour;

uniform mat4 view;
uniform mat4 proj;
uniform mat4 model;
uniform mat4 global_view;

uniform vec3 light_location;
uniform vec3 viewer_location;

void main()
{
	gl_Position =   proj * global_view * view * model * vec4 (vertex_position, 1.0);
	texture_coord = texture;

    frag_positions 			= gl_Position.wxy						;
	frag_normals 			= vertex_normals		* frag_positions;

	frag_light_position 	= light_location 	* frag_positions;
	frag_viewer_position 	= viewer_location 	* frag_positions;

	frag_light_colour  		= vec3(1.0, 1.0, 1.0)					;
}