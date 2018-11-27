// (c) Daniel Dennis 2018

// All GLFW key actions are defined here
// Everything in this file (including cpp file) is my own work

#ifndef KEY_CONTROLS_HPP
#define KEY_CONTROLS_HPP

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "object_relationships.hpp"
#include "camera.hpp"

namespace dd
{   
    static GLchar* WINDOW_NAME = (GLchar*)"Hello Triangle";
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
}

#endif