// (c) Daniel Dennis 2018

#include "gl_object.hpp"

namespace dd
{
    gl_object::gl_object()
    {
        view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -20.0f));
        persp = glm::perspective(45.0f, 1.333f, 0.1f, 1000.0f);
        model = glm::mat4(1.0f);
        global_view = glm::mat4(1.0f);
        viewer_position = light_position = glm::vec3(0.0f);
    }

    gl_object::~gl_object()
    {
        if(compile_object == true)
        {
            glDeleteVertexArrays(1, &VAO);
            delete this_shader;
            delete image_context;
            delete mesh_data;
        }
    }

    packet_t gl_object::get(packet_t data)
    {
        // A goto statement is used here because of the performance critical
        // nature of this particular function
        switch(data.mask)
        {
        case packet_t::empty:       return data;
        case packet_t::view:        goto child_packet;
        case packet_t::persp:       goto child_packet;
        case packet_t::model:       goto child_packet;
        case packet_t::coordinates: goto child_packet;
        case packet_t::global_view: return data;
        case packet_t::move_x:      goto child_packet;
        case packet_t::move_y:      goto child_packet;
        case packet_t::move_z:      goto child_packet;
        case packet_t::rotate_x:    goto child_packet;
        case packet_t::rotate_y:    goto child_packet;
        case packet_t::rotate_z:    goto child_packet;
        case packet_t::render:      return data;
        case packet_t::compile:     return data;
        case packet_t::light_pos:   return data;
        case packet_t::viewer_pos:  return data;
        case packet_t::scale:       return data;  
        }

        // goto label
        child_packet:
        data.mask = packet_t::view;
        child_matrix = view * model;
        data.data = &child_matrix;
        return data;
    }

    void gl_object::set(packet_t data)
    {
        switch(data.mask)
        {
        case packet_t::empty:                                                                                                 return;
        case packet_t::view:        view            = glm::translate(*(glm::mat4*)data.data, offset);                         return;
        case packet_t::persp:       persp           = *(glm::mat4*)data.data;                                                 return;
        case packet_t::model:       model           = *(glm::mat4*)data.data;                                                 return;
        case packet_t::coordinates: offset          = *(glm::vec3*)data.data; view = glm::translate(glm::mat4(1.0), offset);  return;
        case packet_t::global_view: global_view     = *(glm::mat4*)data.data * view;                                          return;
        case packet_t::move_x:      view            = glm::translate(view, glm::vec3(*(float*)data.data, 0.0f, 0.0f));        return;
        case packet_t::move_y:      view            = glm::translate(view, glm::vec3(0.0f, *(float*)data.data, 0.0f));        return;
        case packet_t::move_z:      view            = glm::translate(view, glm::vec3(0.0f, 0.0f, *(float*)data.data));        return;
        case packet_t::rotate_x:    model           = glm::rotate(model, *(float*)data.data, glm::vec3(1.0f, 0.0f, 0.0f));    return;
        case packet_t::rotate_y:    model           = glm::rotate(model, *(float*)data.data, glm::vec3(0.0f, 1.0f, 0.0f));    return;
        case packet_t::rotate_z:    model           = glm::rotate(model, *(float*)data.data, glm::vec3(0.0f, 0.0f, 1.0f));    return;
        case packet_t::render:      this->render();                                                                           return;
        case packet_t::compile: 
            this->compile(((compile_packet_t*)data.data)->mesh_data_input, ((compile_packet_t*)data.data)->texture_file, ((compile_packet_t*)data.data)->shaders); 
        return;
        case packet_t::light_pos:   light_position  = *(glm::vec3*)data.data;                                                 return;
        case packet_t::viewer_pos:  viewer_position = *(glm::vec3*)data.data;                                                 return;
        case packet_t::scale:
            // model = glm::scale(model, glm::vec3(1.0f), *(float*)data.data);
            model = glm::scale(model, glm::vec3(*(float*)data.data, *(float*)data.data, *(float*)data.data));
        return;
        // case packet_t::scale        
        }
        
    }

    void gl_object::compile(char* mesh_data_input, char* texture_file, char** shaders)
    {
        if((!strcmp(mesh_data_input, "null")
        &&  !strcmp(texture_file,    "null")
        &&  !strcmp(shaders[0],      "null")
        &&  !strcmp(shaders[1],      "null")))
        {
            compile_object = false;
        }
        else
        {
            compile_object = true;
        }
        if(compile_object == true)
        {
            this_shader             = new shader_loader(shaders[0], shaders[1]);
            image_context           = new image_loader(texture_file);
            mesh_data               = new model_loader;
            texture_VBO             = image_context->get_location();
            positions_loc           = glGetAttribLocation(this_shader->program, "vertex_position" );
            normals_loc             = glGetAttribLocation(this_shader->program, "vertex_normals"  );
            texture_coord_loc       = glGetAttribLocation(this_shader->program, "texture"         );

            mesh_data->load_mesh(mesh_data_input);
        
            glGenVertexArrays (1, &VAO);
            glBindVertexArray (VAO);

            global_view_location    = glGetUniformLocation(this_shader->program, "global_view"      );
            view_location           = glGetUniformLocation(this_shader->program, "view"             );
            persp_location          = glGetUniformLocation(this_shader->program, "proj"             );
            model_location          = glGetUniformLocation(this_shader->program, "model"            );
            light_location          = glGetUniformLocation(this_shader->program, "light_location"   );
            viewer_location         = glGetUniformLocation(this_shader->program, "viewer_location"  );
            texture_location        = glGetUniformLocation(this_shader->program, "tex"              );
        }
    }

    void gl_object::render()
    {
        if(compile_object)
        {
            glUseProgram(this_shader->program);

            glEnableVertexAttribArray(positions_loc                                 );
            glBindBuffer(GL_ARRAY_BUFFER, mesh_data->get_vertices_VBO()              );
            glVertexAttribPointer (positions_loc, 3, GL_FLOAT, GL_FALSE, 0, NULL    );
            
            glEnableVertexAttribArray(normals_loc                                   );
            glBindBuffer(GL_ARRAY_BUFFER, mesh_data->get_normals_VBO()               );
            glVertexAttribPointer (normals_loc, 3, GL_FLOAT, GL_FALSE, 0, NULL      );

            glEnableVertexAttribArray(texture_coord_loc                             );
            glBindBuffer(GL_ARRAY_BUFFER, mesh_data->get_texture_coord_VBO()         );
            glVertexAttribPointer (texture_coord_loc, 2, GL_FLOAT, GL_FALSE, 0, NULL);

            glViewport(0, 0, 1600, 1200);
            glEnable(GL_DEPTH_TEST);
            
            glUniformMatrix4fv(persp_location       , 1, GL_FALSE, glm::value_ptr(persp)          );
            glUniformMatrix4fv(view_location        , 1, GL_FALSE, glm::value_ptr(view)           );
            glUniformMatrix4fv(model_location       , 1, GL_FALSE, glm::value_ptr(model)          );
            glUniformMatrix4fv(global_view_location , 1, GL_FALSE, glm::value_ptr(global_view)    );
            glUniform3fv      (light_location       , 1, glm::value_ptr(light_position) );
            glUniform3fv      (viewer_location      , 1, glm::value_ptr(viewer_position));

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, texture_VBO);
            glUniform1i(texture_location, 0);

            glDrawArrays (GL_TRIANGLES, 0, mesh_data->get_point_count());
        }
    }
}