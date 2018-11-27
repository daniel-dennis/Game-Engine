// (c) Daniel Dennis 2018

#include "object_relationships.hpp"

namespace dd
{
    // [(id_t) id] sp [(key_press_t) key_press] sp [(mask_t) action] [(float) amount]
    object_relationships::object_relationships(const char* model_file, const char* action_file) : hierarchy_implementation(model_file)
    {
        const unsigned short ID_LEN = 100;
        const unsigned short TOKEN_LEN = 100;
        const unsigned short LINE_LEN = 1000;
        const unsigned short NUMBER_PARAMETERS = 5;
        const char* MODE = "r";

        char str[LINE_LEN];

        // Read object hierarchy file
        FILE* file = fopen(action_file, MODE);
        char curr_id_str[TOKEN_LEN];
        char curr_key_str[TOKEN_LEN];
        char curr_action_str[TOKEN_LEN];
        char curr_amount_str[TOKEN_LEN];

        node_id_t curr_id;
        key_press_t curr_key;
        packet_t::mask_t curr_action;
        float curr_amount;

        if(!file)
        {
            fprintf(stderr, "ERROR: file not found (%s)\n", action_file);
        }

        while(!feof(file))
        {
            fgets(str, LINE_LEN, file);

            // Put into individual strings
            strcpy(curr_id_str,     strtok(str,  " "));
            strcpy(curr_key_str,    strtok(NULL, " "));
            strcpy(curr_action_str, strtok(NULL, " "));
            strcpy(curr_amount_str, strtok(NULL, " "));

            // Parse individual strings
            // id
            char* token = strtok(curr_id_str, ",");
            curr_id.clear();

            while(token)
            {
                id_t curr_val = atoi(token);
                curr_id.push_back(curr_val);
                token = strtok(NULL, ",");
            }

            // key_press
            curr_key = return_key_press(curr_key_str);
            
            // action
            curr_action = return_mask(curr_action_str);

            // amount
            curr_amount = strtof(curr_amount_str, NULL);

            action_t action_to_push;

            action_to_push.step = curr_amount;
            action_to_push.which_function = return_action_func(curr_action);
            action_to_push.address = curr_id;

            switch(curr_key)
            {
            case key_press_t::key_up:
                up_actions.push_back(action_to_push);
            break;
            case key_press_t::key_down:
                down_actions.push_back(action_to_push);
            break;
            case key_press_t::key_left:
                left_actions.push_back(action_to_push);
            break;
            case key_press_t::key_right:
                right_actions.push_back(action_to_push);
            break;
            case key_press_t::loop:
                loop_actions.push_back(action_to_push);
            break;
            case key_press_t::key_comma:
                comma_actions.push_back(action_to_push);
            break;
            case key_press_t::key_fullstop:
                fullstop_actions.push_back(action_to_push);
            break;
            case key_press_t::key_solidus:
                solidus_actions.push_back(action_to_push);
            break;
            case key_press_t::invalid:
            break;
            case key_press_t::key_a:
                key_a_actions.push_back(action_to_push);
            break;
            case key_press_t::key_b:        
                key_b_actions.push_back(action_to_push);
            break;
            case key_press_t::key_c:        
                key_c_actions.push_back(action_to_push);
            break;
            case key_press_t::key_d:        
                key_d_actions.push_back(action_to_push);
            break;
            case key_press_t::key_e:        
                key_e_actions.push_back(action_to_push);
            break;
            case key_press_t::key_f:        
                key_f_actions.push_back(action_to_push);
            break;
            case key_press_t::key_g:        
                key_g_actions.push_back(action_to_push);
            break;
            case key_press_t::key_h:        
                key_h_actions.push_back(action_to_push);
            break;
            case key_press_t::key_i:        
                key_i_actions.push_back(action_to_push);
            break;
            case key_press_t::key_j:        
                key_j_actions.push_back(action_to_push);
            break;
            case key_press_t::key_k:        
                key_k_actions.push_back(action_to_push);
            break;
            case key_press_t::key_l:        
                key_l_actions.push_back(action_to_push);
            break;
            case key_press_t::key_m:        
                key_m_actions.push_back(action_to_push);
            break;
            case key_press_t::key_n:        
                key_n_actions.push_back(action_to_push);
            break;
            case key_press_t::key_o:        
                key_o_actions.push_back(action_to_push);
            break;
            case key_press_t::key_p:        
                key_p_actions.push_back(action_to_push);
            break;
            case key_press_t::key_q:        
                key_q_actions.push_back(action_to_push);
            break;
            case key_press_t::key_r:        
                key_r_actions.push_back(action_to_push);
            break;
            case key_press_t::key_s:        
                key_s_actions.push_back(action_to_push);
            break;
            case key_press_t::key_t:        
                key_t_actions.push_back(action_to_push);
            break;
            case key_press_t::key_u:        
                key_u_actions.push_back(action_to_push);
            break;
            case key_press_t::key_v:        
                key_v_actions.push_back(action_to_push);
            break;
            case key_press_t::key_w:        
                key_w_actions.push_back(action_to_push);
            break;
            case key_press_t::key_x:        
                key_x_actions.push_back(action_to_push);
            break;
            case key_press_t::key_y:        
                key_y_actions.push_back(action_to_push);
            break;
            case key_press_t::key_z:        
                key_z_actions.push_back(action_to_push);
            break;
            case key_press_t::init:        
                init_actions.push_back(action_to_push);
            break;
            }
        }
        fclose(file);
    }

    key_press_t object_relationships::return_key_press(char* str)
    {
        // Clearly not an efficient approach, but time is
        // of the essence in making this project

        if(!strcmp(str, "loop"          )) return key_press_t::loop;
        if(!strcmp(str, "key_up"        )) return key_press_t::key_up;
        if(!strcmp(str, "key_down"      )) return key_press_t::key_down;
        if(!strcmp(str, "key_left"      )) return key_press_t::key_left;
        if(!strcmp(str, "key_right"     )) return key_press_t::key_right;
        if(!strcmp(str, "key_comma"     )) return key_press_t::key_comma;
        if(!strcmp(str, "key_fullstop"  )) return key_press_t::key_fullstop;
        if(!strcmp(str, "key_solidus"   )) return key_press_t::key_solidus;
        if(!strcmp(str, "key_a"         )) return key_press_t::key_a;
        if(!strcmp(str, "key_b"         )) return key_press_t::key_b;
        if(!strcmp(str, "key_c"         )) return key_press_t::key_c;
        if(!strcmp(str, "key_d"         )) return key_press_t::key_d;
        if(!strcmp(str, "key_e"         )) return key_press_t::key_e;
        if(!strcmp(str, "key_f"         )) return key_press_t::key_f;
        if(!strcmp(str, "key_g"         )) return key_press_t::key_g;
        if(!strcmp(str, "key_h"         )) return key_press_t::key_h;
        if(!strcmp(str, "key_i"         )) return key_press_t::key_i;
        if(!strcmp(str, "key_j"         )) return key_press_t::key_j;
        if(!strcmp(str, "key_k"         )) return key_press_t::key_k;
        if(!strcmp(str, "key_l"         )) return key_press_t::key_l;
        if(!strcmp(str, "key_m"         )) return key_press_t::key_m;
        if(!strcmp(str, "key_n"         )) return key_press_t::key_n;
        if(!strcmp(str, "key_o"         )) return key_press_t::key_o;
        if(!strcmp(str, "key_p"         )) return key_press_t::key_p;
        if(!strcmp(str, "key_q"         )) return key_press_t::key_q;
        if(!strcmp(str, "key_r"         )) return key_press_t::key_r;
        if(!strcmp(str, "key_s"         )) return key_press_t::key_s;
        if(!strcmp(str, "key_t"         )) return key_press_t::key_t;
        if(!strcmp(str, "key_u"         )) return key_press_t::key_u;
        if(!strcmp(str, "key_v"         )) return key_press_t::key_v;
        if(!strcmp(str, "key_w"         )) return key_press_t::key_w;
        if(!strcmp(str, "key_x"         )) return key_press_t::key_x;
        if(!strcmp(str, "key_y"         )) return key_press_t::key_y;
        if(!strcmp(str, "key_z"         )) return key_press_t::key_z;
        if(!strcmp(str, "init"          )) return key_press_t::init;

        std::cerr << "ERROR: incorrect key_press_t value\n";
        return key_press_t::invalid;
    }

    packet_t::mask_t object_relationships::return_mask(char* str)
    {
        // Ditto as with return_key_press
        if(!strcmp(str, "view"))         return packet_t::mask_t::view;
        if(!strcmp(str, "persp"))        return packet_t::mask_t::persp;
        if(!strcmp(str, "model"))        return packet_t::mask_t::model;
        if(!strcmp(str, "coordinates"))  return packet_t::mask_t::coordinates;
        if(!strcmp(str, "global_view"))  return packet_t::mask_t::global_view;
        if(!strcmp(str, "move_x"))       return packet_t::mask_t::move_x;
        if(!strcmp(str, "move_y"))       return packet_t::mask_t::move_y;
        if(!strcmp(str, "move_z"))       return packet_t::mask_t::move_z;
        if(!strcmp(str, "rotate_x"))     return packet_t::mask_t::rotate_x;
        if(!strcmp(str, "rotate_y"))     return packet_t::mask_t::rotate_y;
        if(!strcmp(str, "rotate_z"))     return packet_t::mask_t::rotate_z;
        if(!strcmp(str, "scale"))        return packet_t::mask_t::scale;

        std::cerr << "ERROR: incorrect mask_t value\n";
        return packet_t::mask_t::empty;
    }

    void object_relationships::key_handler(key_press_t keypress)
    {
        switch(keypress)
        {
        case key_press_t::loop:
            for(int i = 0; i < loop_actions.size(); i++)
            {
                (loop_actions[i].which_function)(loop_actions[i].address, loop_actions[i].step, objects[(loop_actions[i].address)[0]]);
            }
        return;
        case key_press_t::key_up:
            for(int i = 0; i < up_actions.size(); i++)
            {
                (up_actions[i].which_function)(up_actions[i].address, up_actions[i].step, objects[(up_actions[i].address)[0]]);
            }
        return;
        case key_press_t::key_down:
            for(int i = 0; i < down_actions.size(); i++)
            {
                (down_actions[i].which_function)(down_actions[i].address, down_actions[i].step, objects[(down_actions[i].address)[0]]);
            }
        return;
        case key_press_t::key_left:
            for(int i = 0; i < left_actions.size(); i++)
            {
                (right_actions[i].which_function)(right_actions[i].address, right_actions[i].step, objects[(right_actions[i].address)[0]]);
            }
        return;
        case key_press_t::key_right:
            for(int i = 0; i < right_actions.size(); i++)
            {
                (left_actions[i].which_function)(left_actions[i].address, left_actions[i].step, objects[(left_actions[i].address)[0]]);
            }
        return;
        case key_press_t::key_comma:
            for(int i = 0; i < comma_actions.size(); i++)
            {
                (comma_actions[i].which_function)(comma_actions[i].address, comma_actions[i].step, objects[(comma_actions[i].address)[0]]);
            }
        return;
        case key_press_t::key_fullstop:
            for(int i = 0; i < fullstop_actions.size(); i++)
            {
                (fullstop_actions[i].which_function)(fullstop_actions[i].address, fullstop_actions[i].step, objects[(fullstop_actions[i].address)[0]]);
            }
        return;
        case key_press_t::key_solidus:
            for(int i = 0; i < solidus_actions.size(); i++)
            {
                (solidus_actions[i].which_function)(solidus_actions[i].address, solidus_actions[i].step, objects[(solidus_actions[i].address)[0]]);
            }
        return;
        case key_press_t::key_a:
            for(int i = 0; i < key_a_actions.size(); i++)
            {
                (key_a_actions[i].which_function)(key_a_actions[i].address, key_a_actions[i].step, objects[(key_a_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_b:
            for(int i = 0; i < key_b_actions.size(); i++)
            {
                (key_b_actions[i].which_function)(key_b_actions[i].address, key_b_actions[i].step, objects[(key_b_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_c:
            for(int i = 0; i < key_c_actions.size(); i++)
            {
                (key_c_actions[i].which_function)(key_c_actions[i].address, key_c_actions[i].step, objects[(key_c_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_d:
            for(int i = 0; i < key_d_actions.size(); i++)
            {
                (key_d_actions[i].which_function)(key_d_actions[i].address, key_d_actions[i].step, objects[(key_d_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_e:
            for(int i = 0; i < key_e_actions.size(); i++)
            {
                (key_e_actions[i].which_function)(key_e_actions[i].address, key_e_actions[i].step, objects[(key_e_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_f:
            for(int i = 0; i < key_f_actions.size(); i++)
            {
                (key_f_actions[i].which_function)(key_f_actions[i].address, key_f_actions[i].step, objects[(key_f_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_g:
            for(int i = 0; i < key_g_actions.size(); i++)
            {
                (key_g_actions[i].which_function)(key_g_actions[i].address, key_g_actions[i].step, objects[(key_g_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_h:
            for(int i = 0; i < key_h_actions.size(); i++)
            {
                (key_h_actions[i].which_function)(key_h_actions[i].address, key_h_actions[i].step, objects[(key_h_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_i:
            for(int i = 0; i < key_i_actions.size(); i++)
            {
                (key_i_actions[i].which_function)(key_i_actions[i].address, key_i_actions[i].step, objects[(key_i_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_j:
            for(int i = 0; i < key_j_actions.size(); i++)
            {
                (key_j_actions[i].which_function)(key_j_actions[i].address, key_j_actions[i].step, objects[(key_j_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_k:
            for(int i = 0; i < key_k_actions.size(); i++)
            {
                (key_k_actions[i].which_function)(key_k_actions[i].address, key_k_actions[i].step, objects[(key_k_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_l:
            for(int i = 0; i < key_l_actions.size(); i++)
            {
                (key_l_actions[i].which_function)(key_l_actions[i].address, key_l_actions[i].step, objects[(key_l_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_m:
            for(int i = 0; i < key_m_actions.size(); i++)
            {
                (key_m_actions[i].which_function)(key_m_actions[i].address, key_m_actions[i].step, objects[(key_m_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_n:
            for(int i = 0; i < key_n_actions.size(); i++)
            {
                (key_n_actions[i].which_function)(key_n_actions[i].address, key_n_actions[i].step, objects[(key_n_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_o:
            for(int i = 0; i < key_o_actions.size(); i++)
            {
                (key_o_actions[i].which_function)(key_o_actions[i].address, key_o_actions[i].step, objects[(key_o_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_p:
            for(int i = 0; i < key_p_actions.size(); i++)
            {
                (key_p_actions[i].which_function)(key_p_actions[i].address, key_p_actions[i].step, objects[(key_p_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_q:
            for(int i = 0; i < key_q_actions.size(); i++)
            {
                (key_q_actions[i].which_function)(key_q_actions[i].address, key_q_actions[i].step, objects[(key_q_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_r:
            for(int i = 0; i < key_r_actions.size(); i++)
            {
                (key_r_actions[i].which_function)(key_r_actions[i].address, key_r_actions[i].step, objects[(key_r_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_s:
            for(int i = 0; i < key_s_actions.size(); i++)
            {
                (key_s_actions[i].which_function)(key_s_actions[i].address, key_s_actions[i].step, objects[(key_s_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_t:
            for(int i = 0; i < key_t_actions.size(); i++)
            {
                (key_t_actions[i].which_function)(key_t_actions[i].address, key_t_actions[i].step, objects[(key_t_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_u:
            for(int i = 0; i < key_u_actions.size(); i++)
            {
                (key_u_actions[i].which_function)(key_u_actions[i].address, key_u_actions[i].step, objects[(key_u_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_v:
            for(int i = 0; i < key_v_actions.size(); i++)
            {
                (key_v_actions[i].which_function)(key_v_actions[i].address, key_v_actions[i].step, objects[(key_v_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_w:
            for(int i = 0; i < key_w_actions.size(); i++)
            {
                (key_w_actions[i].which_function)(key_w_actions[i].address, key_w_actions[i].step, objects[(key_w_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_x:
            for(int i = 0; i < key_x_actions.size(); i++)
            {
                (key_x_actions[i].which_function)(key_x_actions[i].address, key_x_actions[i].step, objects[(key_x_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_y:
            for(int i = 0; i < key_y_actions.size(); i++)
            {
                (key_y_actions[i].which_function)(key_y_actions[i].address, key_y_actions[i].step, objects[(key_y_actions[i].address)[0]]);
            }
        break;    
        case key_press_t::key_z:
            for(int i = 0; i < key_z_actions.size(); i++)
            {
                (key_z_actions[i].which_function)(key_z_actions[i].address, key_z_actions[i].step, objects[(key_z_actions[i].address)[0]]);
            }
        break;
        case key_press_t::init:
            for(int i = 0; i < init_actions.size(); i++)
            {
                (init_actions[i].which_function)(init_actions[i].address, init_actions[i].step, objects[(init_actions[i].address)[0]]);
            }
        break;
        default:
            std::cerr << "ERROR: invalid key_press_t passed\n";
        return;
        }
    }

    void function_move_x(node_id_t id, float val, hierarchy<gl_object, packet_t>* location)
    {
        packet_t packet(packet_t::move_x);
        packet.data = &val;
        location->set_element(id, packet);
        return;
    }

    void function_move_y(node_id_t id, float val, hierarchy<gl_object, packet_t>* location)
    {
        packet_t packet(packet_t::move_y);
        packet.data = &val;
        location->set_element(id, packet);
        return;
    }

    void function_move_z(node_id_t id, float val, hierarchy<gl_object, packet_t>* location)
    {
        packet_t packet(packet_t::move_z);
        packet.data = &val;
        location->set_element(id, packet);
        return;
    }

    void function_rotate_x(node_id_t id, float val, hierarchy<gl_object, packet_t>* location)
    {
        packet_t packet(packet_t::rotate_x);
        packet.data = &val;
        location->set_element(id, packet);
        return;
    }

    void function_rotate_y(node_id_t id, float val, hierarchy<gl_object, packet_t>* location)
    {
        packet_t packet(packet_t::rotate_y);
        packet.data = &val;
        location->set_element(id, packet);
        return;
    }

    void function_rotate_z(node_id_t id, float val, hierarchy<gl_object, packet_t>* location)
    {
        packet_t packet(packet_t::rotate_z);
        packet.data = &val;
        location->set_element(id, packet);
        return;
    }

    void scale(node_id_t id, float val, hierarchy<gl_object, packet_t>* location)
    {
        packet_t packet(packet_t::scale);
        packet.data = &val;
        location->set_element(id, packet);
        return;
    }

    void (*object_relationships::return_action_func(packet_t::mask_t action))(node_id_t, float, hierarchy<gl_object, packet_t>*)
    {
        switch(action)
        {
        case packet_t::mask_t::move_x:      return &function_move_x;
        case packet_t::mask_t::move_y:      return &function_move_y;
        case packet_t::mask_t::move_z:      return &function_move_z;
        case packet_t::mask_t::empty:       return NULL;
        case packet_t::mask_t::view:        return NULL;
        case packet_t::mask_t::persp:       return NULL;
        case packet_t::mask_t::model:       return NULL;
        case packet_t::mask_t::coordinates: return NULL;
        case packet_t::mask_t::global_view: return NULL;
        case packet_t::mask_t::rotate_x:    return &function_rotate_x;
        case packet_t::mask_t::rotate_y:    return &function_rotate_y;
        case packet_t::mask_t::rotate_z:    return &function_rotate_z;
        case packet_t::mask_t::scale:       return &scale;
        default:                            return NULL;
        }
    }
}