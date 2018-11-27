// (c) Daniel Dennis 2018

#include "hierarchy_implementation.hpp"

namespace dd
{
    hierarchy_implementation::hierarchy_implementation(const char* file_path)
    {
        const unsigned short ID_LEN = 100;
        const unsigned short TOKEN_LEN = 100;
        const unsigned short LINE_LEN = 1000;
        const unsigned char SHADER_NUM = 2;
        const unsigned short NUMBER_PARAMETERS = 5;
        const char* MODE = "r";
        char* shader_ptrs[SHADER_NUM]; // for passing vertex and fragment shader into gl_object contructor

        // Class setup
        num_models = -1;

        // Read object hierarchy file
        char str[LINE_LEN];
        char id[ID_LEN];
        char file_name[TOKEN_LEN];
        char texture_file[TOKEN_LEN];
        char vertex_shader[TOKEN_LEN];
        char frag_shader[TOKEN_LEN];
        float x_pos, y_pos, z_pos;
        node_id_t curr_id;
        FILE* file = fopen(file_path, MODE);
        if(!file)
        {
            fprintf(stderr, "ERROR: file not found (%s)\n", file_path);
        }
        // objects.resize(100);

        while(!feof(file))
        {
            fgets(str, LINE_LEN, file);
            if(str[0] == '#') // If there the line has been commented out
            {
                continue;
            }
            // Read parameters from file
            strcpy(id,              strtok(str,  " ")   );          // Vector ID
            strcpy(file_name,       strtok(NULL, " ")   );          // Name of model to import
            strcpy(texture_file,    strtok(NULL, " ")   );          // Name of texture to import
            strcpy(vertex_shader,   strtok(NULL, " ")   );          // Name of vertex shader to import
            strcpy(frag_shader,     strtok(NULL, " ")   );          // Name of fragment shader to import
            x_pos = strtof(         strtok(NULL, " ")   , NULL);    // X relative to parent
            y_pos = strtof(         strtok(NULL, " ")   , NULL);    // Y relative to parent
            z_pos = strtof(         strtok(NULL, "\n")  , NULL);    // Z relative to parent

            // Process Vector ID into actual vector
            char* token = strtok(id, ",");
            curr_id.clear();

            while(token)
            {
                id_t curr_val = atoi(token);
                curr_id.push_back(curr_val);
                token = strtok(NULL, ",");
            }
            

            if(curr_id[0] > num_models)
            // If hierarchy does not exist
            {
                num_models++;
                hierarchy<gl_object, packet_t>* new_hierarchy = new hierarchy<gl_object, packet_t>;
                objects.push_back(new_hierarchy);
                objects.back()->create_family(num_models);
            }
            else
            // Push to hierarchy
            {
                id_t temp_last = curr_id.back();
                curr_id.pop_back();
                objects.back()->insert_element(curr_id);
                curr_id.push_back(temp_last);
            }

            // object_ptrs.push_back(objects.back()->get_address(curr_id));

            // Add in parameters;
            packet_t new_packet(packet_t::coordinates);
            glm::vec3 vector_data(x_pos, y_pos, z_pos);
            new_packet.data = &vector_data;
            objects[num_models]->set_element(curr_id, new_packet);

            // Setup shader file location pointer array
            shader_ptrs[0] = vertex_shader;
            shader_ptrs[1] = frag_shader;

            // Setup new intstance of gl_object
            new_packet.mask = packet_t::compile;
            compile_packet_t compile_packet;
            compile_packet.mesh_data_input = file_name;
            compile_packet.texture_file = texture_file;
            compile_packet.shaders = shader_ptrs;
            new_packet.data = &compile_packet;
            objects[num_models]->set_element(curr_id, new_packet);
        }

        fclose(file);
    }

    hierarchy_implementation::~hierarchy_implementation()
    {
        for(int i = 0; i < objects.size(); i++)
        {
            delete objects[i];
        }   
    }
        
    void hierarchy_implementation::render_all_models()
    {
        packet_t new_packet(packet_t::render);
        for(int i = 0; i < objects.size(); i++)
        {
            objects[i]->broadcast(new_packet);
        }
    }

    void hierarchy_implementation::change_camera(glm::mat4& camera)
    {
        packet_t new_packet(packet_t::global_view);
        new_packet.data = &camera;
        for(int i = 0; i < objects.size(); i++)
        {
            objects[i]->broadcast(new_packet);
        }
    }

    void hierarchy_implementation::change_view(glm::mat4& view)
    {
        packet_t new_packet(packet_t::global_view);
        new_packet.data = &view;
        for(int i = 0; i < objects.size(); i++)
        {
            objects[i]->broadcast(new_packet);
        }
    }

    void hierarchy_implementation::change_viewer_pos(glm::vec3& data)
    {
        packet_t new_packet(packet_t::viewer_pos);
        new_packet.data = &data;
        for(int i = 0; i < objects.size(); i++)
        {
            objects[i]->broadcast(new_packet);
        }
    }

    void hierarchy_implementation::change_light_pos(glm::vec3& data)
    {
        packet_t new_packet(packet_t::light_pos);
        new_packet.data = &data;
        for(int i = 0; i < objects.size(); i++)
        {
            objects[i]->broadcast(new_packet);
        }
    }

}