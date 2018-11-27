// (c) Daniel Dennis 2018

#ifndef GL_OBJECT_HPP
#define GL_OBJECT_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <cstring>

#include "shader_loader.hpp"
#include "model_loader.hpp"
#include "image_loader.hpp"

namespace dd
{
    typedef struct packet_t
    {
        // Any changes to this enum must be reflected in:
        // packet_t::mask_t object_relationships::return_mask(char* str)
        // void gl_object::set(packet_t data)
        typedef enum mask
        {
            empty,
            view, 
            persp, 
            model, 
            coordinates,
            global_view,

            move_x,
            move_y,
            move_z,

            rotate_x,
            rotate_y,
            rotate_z,

            render,
            compile,
            
            light_pos,
            viewer_pos,

            scale
        } mask_t;

        mask_t mask;
        void* data;

        packet_t(mask_t mask_in){ mask = mask_in; }
    } packet_t;

    typedef struct compile_packet_t
    {
        char* mesh_data_input;
        char* texture_file;
        char** shaders;
    } compile_packet_t;

    class gl_object
    {
    private:
        // GL variables
        GLuint positions_loc, normals_loc, texture_coord_loc;
        GLuint VAO;
        
        GLint view_location;
        GLint persp_location;
        GLint model_location;
        GLint global_view_location;
        GLint texture_location;
        GLint light_location;
        GLint viewer_location;
        GLint texture_VBO;

        glm::mat4 view;
        glm::mat4 persp;
        glm::mat4 model;
        glm::mat4 global_view;
        glm::vec3 viewer_position;
        glm::vec3 light_position;
        
        // Helper classes
        model_loader* mesh_data;
        shader_loader* this_shader;
        image_loader* image_context;

        // Hierarchy variables
        glm::mat4 child_matrix;
        glm::vec3 offset;

        bool compile_object;
    public:
        gl_object();
        ~gl_object();
        packet_t get(packet_t data);
        void set(packet_t data);

        void compile(char* mesh_data_input, char* texture_file, char** shaders);
        void render();
    };
}

#endif