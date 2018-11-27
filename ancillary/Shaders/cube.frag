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
    // vec3 light_colour   = vec3(1.0, 1.0, 1.0);
    vec3 normalised_normal = normalize(frag_normals);
    vec3 light_direction = normalize(frag_light_position - frag_positions);

    // Ambient Light
	float ambient_strength = 0.0;
    vec3 ambient = ambient_strength * texture(tex, texture_coord).xyz;

    // Diffuse light
    float diff = max(dot(normalised_normal, light_direction), 0.5);
    vec3 diffuse = diff * frag_light_colour;

    // Specular light
    float specular_strength = 0.5;

    vec3 view_dir = normalize(frag_viewer_position - frag_positions);
    vec3 reflect_dir = reflect(-light_direction, normalised_normal); 

    float spec = pow(max(dot(view_dir, reflect_dir), 0.5), 64);
    vec3 specular = specular_strength * spec * frag_light_colour; 

    // Combine for phong illumination model
    vec3 result = (ambient + diffuse + specular);

    frag_colour = vec4(result, 0.0) * texture(tex, texture_coord);
}