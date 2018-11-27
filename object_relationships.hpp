// (c) Daniel Dennis 2018

// Implements actions for objects specified in a file passed to
// this class in the constructor
// Everything in this class is my own work

#ifndef OBJECT_RELATIONSHIPS_HPP
#define OBJECT_RELATIONSHIPS_HPP

#include <iostream>
#include <cstring>
#include <vector>

#include "hierarchy_implementation.hpp"
#include "gl_object.hpp"
#include "hierarchy.hpp"

namespace dd
{
    // Any changes to this enum must be reflected in:
    // key_press_t object_relationships::return_key_press(char* str)
    // void object_relationships::key_handler(key_press_t keypress)
    // void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    
    typedef enum key_press
    {
        loop,
        key_up,
        key_down,
        key_left,
        key_right,
        key_comma,
        key_fullstop,
        key_solidus,
        key_a,
        key_b,
        key_c,
        key_d,
        key_e,
        key_f,
        key_g,
        key_h,
        key_i,
        key_j,
        key_k,
        key_l,
        key_m,
        key_n,
        key_o,
        key_p,
        key_q,
        key_r,
        key_s,
        key_t,
        key_u,
        key_v,
        key_w,
        key_x,
        key_y,
        key_z,
        init,
        invalid
    } key_press_t;

    typedef struct packet_stack_t
    {
        packet_t packet;
        node_id_t address;
    } packet_stack_t;

    // [(id_t) id] sp [(key_press_t) key_press] sp [(mask_t) action] [(float) amount]

    class object_relationships : public hierarchy_implementation
    {
    private:
        const char* FILE_NAME = "actions.txt";
        key_press_t return_key_press(char* str);
        packet_t::mask_t return_mask(char* str);

        // void function_move_x(node_id_t id, float val);
        // void function_move_y(node_id_t id, float val);
        // void function_move_z(node_id_t id, float val);

        // void function_rotate_x(node_id_t id, float val);
        // void function_rotate_y(node_id_t id, float val);
        // void function_rotate_z(node_id_t id, float val);


        typedef struct action
        {
            void (*which_function)(node_id_t, float, hierarchy<gl_object, packet_t>*);
            float step;
            node_id_t address;
        } action_t;

        std::vector<object_relationships::action_t> up_actions;
        std::vector<action_t> down_actions;
        std::vector<action_t> left_actions;
        std::vector<action_t> right_actions;
        std::vector<action_t> comma_actions;
        std::vector<action_t> fullstop_actions;
        std::vector<action_t> solidus_actions;
        std::vector<action_t> loop_actions;
        std::vector<action_t> key_a_actions;
        std::vector<action_t> key_b_actions;
        std::vector<action_t> key_c_actions;
        std::vector<action_t> key_d_actions;
        std::vector<action_t> key_e_actions;
        std::vector<action_t> key_f_actions;
        std::vector<action_t> key_g_actions;
        std::vector<action_t> key_h_actions;
        std::vector<action_t> key_i_actions;
        std::vector<action_t> key_j_actions;
        std::vector<action_t> key_k_actions;
        std::vector<action_t> key_l_actions;
        std::vector<action_t> key_m_actions;
        std::vector<action_t> key_n_actions;
        std::vector<action_t> key_o_actions;
        std::vector<action_t> key_p_actions;
        std::vector<action_t> key_q_actions;
        std::vector<action_t> key_r_actions;
        std::vector<action_t> key_s_actions;
        std::vector<action_t> key_t_actions;
        std::vector<action_t> key_u_actions;
        std::vector<action_t> key_v_actions;
        std::vector<action_t> key_w_actions;
        std::vector<action_t> key_x_actions;
        std::vector<action_t> key_y_actions;
        std::vector<action_t> key_z_actions;
        std::vector<action_t> init_actions;

        void (*return_action_func(packet_t::mask_t action))(node_id_t, float, hierarchy<gl_object, packet_t>*);
    public:
        object_relationships(const char* model_file, const char* action_file);
        void key_handler(key_press_t keypress);
    };
}

#endif