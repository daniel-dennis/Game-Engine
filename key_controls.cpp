// (c) Daniel Dennis 2018

#include "key_controls.hpp"

namespace dd
{
    extern object_relationships* objects_global;
    extern camera* main_camera;
    bool mouse_disabled = false;
    
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if ((action == GLFW_REPEAT) || (action == GLFW_PRESS))
        {
            switch(key)
            {
            case GLFW_KEY_UP:
                objects_global->key_handler(key_press_t::key_up);
            break;
            case GLFW_KEY_DOWN:
                objects_global->key_handler(key_press_t::key_down);
            break;
            case GLFW_KEY_LEFT:
                objects_global->key_handler(key_press_t::key_left);
            break;
            case GLFW_KEY_RIGHT:
                objects_global->key_handler(key_press_t::key_right);
            break;
            case GLFW_KEY_LEFT_BRACKET:
                main_camera->move_x(0.5f);
            break;
            case GLFW_KEY_SEMICOLON:
                main_camera->move_y(-0.5f);
            break;
            case GLFW_KEY_APOSTROPHE:
                main_camera->move_x(-0.5f);
            break;
            case GLFW_KEY_BACKSLASH:
                main_camera->move_y(0.5f);
            break;
            case GLFW_KEY_COMMA:
                objects_global->key_handler(key_press_t::key_comma);
            break;
            case GLFW_KEY_PERIOD:
                objects_global->key_handler(key_press_t::key_fullstop);
            break;
            case GLFW_KEY_SLASH:
                objects_global->key_handler(key_press_t::key_solidus);
            break;
            case GLFW_KEY_A:
                objects_global->key_handler(key_press_t::key_a);
                main_camera->move_y(-0.5f);
            break;
            case GLFW_KEY_B:
                objects_global->key_handler(key_press_t::key_b);
            break;
            case GLFW_KEY_C:
                objects_global->key_handler(key_press_t::key_c);
            break;
            case GLFW_KEY_D:
                objects_global->key_handler(key_press_t::key_d);
                main_camera->move_y(0.5f);
            break;
            case GLFW_KEY_E:
                objects_global->key_handler(key_press_t::key_e);
            break;
            case GLFW_KEY_F:
                objects_global->key_handler(key_press_t::key_f);
            break;
            case GLFW_KEY_G:
                objects_global->key_handler(key_press_t::key_g);
            break;
            case GLFW_KEY_H:
                objects_global->key_handler(key_press_t::key_h);
            break;
            case GLFW_KEY_I:
                objects_global->key_handler(key_press_t::key_i);
            break;
            case GLFW_KEY_J:
                objects_global->key_handler(key_press_t::key_j);
            break;
            case GLFW_KEY_K:
                objects_global->key_handler(key_press_t::key_k);
            break;
            case GLFW_KEY_L:
                objects_global->key_handler(key_press_t::key_l);
            break;
            case GLFW_KEY_M:
                objects_global->key_handler(key_press_t::key_m);
            break;
            case GLFW_KEY_N:
                objects_global->key_handler(key_press_t::key_n);
            break;
            case GLFW_KEY_O:
                objects_global->key_handler(key_press_t::key_o);
            break;
            case GLFW_KEY_P:
                objects_global->key_handler(key_press_t::key_p);
            break;
            case GLFW_KEY_Q:
                objects_global->key_handler(key_press_t::key_q);
            break;
            case GLFW_KEY_R:
                objects_global->key_handler(key_press_t::key_r);
            break;
            case GLFW_KEY_S:
                objects_global->key_handler(key_press_t::key_s);
                main_camera->move_x(-0.5f);
            break;
            case GLFW_KEY_T:
                objects_global->key_handler(key_press_t::key_t);
            break;
            case GLFW_KEY_U:
                objects_global->key_handler(key_press_t::key_u);
            break;
            case GLFW_KEY_V:
                objects_global->key_handler(key_press_t::key_v);
            break;
            case GLFW_KEY_W:
                objects_global->key_handler(key_press_t::key_w);
                main_camera->move_x(0.5f);
            break;
            case GLFW_KEY_X:
                objects_global->key_handler(key_press_t::key_x);
            break;
            case GLFW_KEY_Y:
                objects_global->key_handler(key_press_t::key_y);
            break;
            case GLFW_KEY_Z:
                objects_global->key_handler(key_press_t::key_z);
            break;
            
            case GLFW_KEY_ESCAPE:
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                mouse_disabled = false;
            break;
            }
        }
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        mouse_disabled = true;
    }

    void mouse_callback(GLFWwindow* window, double xpos, double ypos)
    {
        if(mouse_disabled)
        {
            main_camera->mouse_handler(xpos, ypos);
        }
    }
}