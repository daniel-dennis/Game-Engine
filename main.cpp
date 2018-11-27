// (c) Daniel Dennis 2018

// Everythng in this file is my own work

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>

#include "object_relationships.hpp"
#include "camera.hpp"
#include "key_controls.hpp"

namespace dd
{
    // Global variables
    object_relationships* objects_global;
    camera* main_camera;

    // Global constants
    const char  NUM_FILES   = 2;
    const short HEIGHT      = 600;
    const short WIDTH       = 800;

    // Functions in this file
    GLint initial_setup(GLuint width, GLuint height, GLchar* window_name, GLFWwindow*& window);
}

int main(int argc, char** argv)
{
    if(argc != (dd::NUM_FILES + 1))
    {
        std::cerr << "Error: incorrect number of arguments\n"
                  << "\tThe correct syntax is:\n"
                  << "\t./program [object structures file] [object actions file]\n";
        return EXIT_FAILURE;
    }

    GLFWwindow* window;
    if(dd::initial_setup(dd::WIDTH, dd::HEIGHT, dd::WINDOW_NAME, window) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }

    dd::objects_global = new dd::object_relationships(argv[1], argv[2]);
    dd::main_camera = new dd::camera(dd::WIDTH, dd::HEIGHT);

    glfwSetWindowPos(window, 0, 0);
    glfwSetWindowPos(window, 100, 100);

    dd::objects_global->key_handler(dd::key_press_t::init);
    
    #ifdef __APPLE__
    {
        // This is an ugly workaround for a bug in GLFW present in macOS where
        // the window doesn't show anything unless it is manually moved by the
        // user.
        int x, y;
        glfwPollEvents();
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwGetWindowPos(window, &x, &y);
        glfwSetWindowPos(window, ++x, y);
    }
    #endif

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Handle any loop events specified
        dd::objects_global->key_handler(dd::key_press_t::loop);
        
        // Update the camera
        dd::objects_global->change_camera(dd::main_camera->get_view());
        
        // Update lights
        dd::objects_global->change_viewer_pos(dd::main_camera->get_cam_position());

        // Render the current state
        dd::objects_global->render_all_models();

        glfwSwapBuffers(window);

    }
    glfwTerminate();
    delete dd::objects_global;
    delete dd::main_camera;
    return EXIT_SUCCESS;
}

namespace dd
{
    GLint initial_setup(GLuint width, GLuint height, GLchar* window_name, GLFWwindow*& window)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

        window = glfwCreateWindow( width, height, window_name, nullptr, nullptr );
        glfwSetKeyCallback(window, dd::key_callback);
        glfwSetMouseButtonCallback(window, dd::mouse_button_callback);
        glfwSetCursorPosCallback(window, dd::mouse_callback); 

        GLint screenWidth, screenHeight;
        glfwGetFramebufferSize(window, &screenWidth, &screenHeight);
        if(window == nullptr)
        {
            std::cerr << "Error: failed to create GLFW window" << std::endl;
            glfwTerminate();
            return EXIT_FAILURE;
        }
        glfwMakeContextCurrent(window);
        glewExperimental = GL_TRUE;
        if(GLEW_OK != glewInit())
        {
            std::cerr << "Error: failed to initialize GLEW" << std::endl;
            return EXIT_FAILURE;
        }

        return EXIT_SUCCESS;
    }
}